#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hd.h"

hd * hd_create_part(long _psize) {
    if ((_psize % HDBLOCKSIZE) != 0)
	return NULL;

    hd *hd = calloc(1, sizeof(hd));

    if (hd != NULL) {
	hd->size = _psize;
	hd->free = _psize;
    }

    return hd;
}

int hd_destroy(hd **_hd) {
    if (*_hd == NULL)
	return ERR_NO_HD;

    free(*_hd);

    *_hd = NULL;

    return SUCCESS;
}
int hd_insert_file(hd *_hd, char *_name, long _fsize) {
    if (_hd == NULL)
	return ERR_NO_HD;

    if (_name == NULL)
	return ERR_FILE_NAME;

    if (_fsize > FMAXSIZE)
	return ERR_FILE_TO_BIG;

    if (strlen(_name) > NAMELEN)
	return ERR_FILE_NAME;

    if (_hd->free < _fsize) {
	return ERR_NO_SPACE;
    }

    if (hd_find_file(_hd, _name) != NULL)
	return ERR_FILE_EXIST;

    file *f = calloc(1, sizeof(file));

    if (f == NULL)
	return ERR_FILE_MALLOC;

    int fs = 0;

    int bytes = ((_fsize / HDBLOCKSIZE) + 1) * HDBLOCKSIZE;

    file *p = _hd->ftable;
    file *pp = _hd->ftable;

    if (_hd->ftable == NULL) {
	_hd->ftable = f;
	f->next = NULL;
	f->addr = 0;
    } else {
	while (p != NULL) {
	    fs = p->addr - (pp->addr + pp->size);
	    if (fs > bytes ) {
		break;
	    }
	    pp = p;
	    p = p->next;
	}

	pp->next = f;
	if (p == NULL) {
	    f->next = NULL;
	} else {
	    f->next = p;
	}

	f->addr = ((pp->addr + pp->size) / HDBLOCKSIZE + 1) * HDBLOCKSIZE;

    }

    strcpy(f->name, _name);
    f->size = _fsize;
    _hd->free -= bytes;

    return SUCCESS;
}

file * hd_find_file(hd *_hd, char *_name) {
    if (_hd == NULL)
	return NULL;

    if (_hd->ftable == NULL)
	return NULL;

    if (_name == NULL)
	return NULL;

    if (strlen(_name) > NAMELEN)
	return NULL;

    file *p = _hd->ftable;

    while (p != NULL) {
	if (strcmp(p->name, _name) == 0)
	    return p;
	p = p->next;
    }

    return NULL;
}

int hd_remove_file(hd *_hd, char *_name) {
    if (_hd == NULL)
	return ERR_NO_HD;

    if (_hd->ftable == NULL)
	return EMPTY_HD;

    if (_name == NULL)
	return ERR_FILE_NAME;

    if (strlen(_name) > NAMELEN)
	return ERR_FILE_NAME;

    file *p = _hd->ftable;
    file *pp = _hd->ftable;
    int bytes = 0;

    while (p != NULL) {
	if (strcmp(p->name, _name) == 0) {
	    if (p == pp) {
		_hd->ftable = p->next;
	    }
	    pp->next = p->next;
	    bytes = (p->size / HDBLOCKSIZE) * HDBLOCKSIZE;
	    _hd->free += bytes; 
	    free(p);
	    return SUCCESS;
	}
	pp = p;
	p = p->next;
    }

    return FILE_NOT_FOUND;
}

int hd_optimize(hd *_hd) {
    if (_hd == NULL)
	return ERR_NO_HD;

    if (_hd->ftable == NULL)
	return EMPTY_HD;

    file *p = _hd->ftable->next;
    file *pp = _hd->ftable;

    while (p != NULL) {
	p->addr = ((pp->addr + pp->size) / HDBLOCKSIZE + 1) * HDBLOCKSIZE;
	pp = p;
	p = p->next;
    }

    return SUCCESS;
}

void hd_ls(hd *_hd) {
    if (_hd == NULL)
	return;

    if (_hd->ftable == NULL)
	return;

    file * p = _hd->ftable;

    while (p != NULL) {
	printf("[ADDR: %ld] [SIZE: %ld] %s\n", p->addr, p->size, p->name);
	p = p->next;
    }
}

void hd_free(hd *_hd) {
    if (_hd == NULL)
	return;
    printf("Espaco livre: %ld\n", _hd->free);
}

void hd_print_out(hd *_hd) {
    if (_hd == NULL)
	return;

    if (_hd->ftable == NULL)
	return;

    file * p = _hd->ftable;

    int block = _hd->size / PRINTBLOCK;
    int blocks[PRINTBLOCK] = {};
    int i = 0, tmp = 0;

    printf("\n\n");
    while ( p != NULL) {
	i = p->addr/block;
	blocks[i]+= p->size%block;
	if (p->size >= block) {
	    tmp = block - blocks[i];
	    blocks[i] = block;
	    tmp = p->size - tmp;
	    while (tmp != 0) {
		i++;
		if (tmp >= block) {
		    blocks[i] = block;
		    tmp-=block;
		} else {
		    blocks[i] = tmp;
		    tmp = 0;
		}
	    }
	}
	p = p->next;
    }

    /*onde C é ' ', '-' ou '#', dependendo se 75 < P <= 100, 25 < P <= 75 ou 0 <= P <= 25, respectivamente. Caso um arquivo não possa ser inserido por falta de espaço, seu programa deve produzir uma linha contendo a expressão ERRO: disco cheio; nesse caso, operações subseqüentes do caso de teste devem ser ignoradas. */
    int blockper;
    for (i = 0; i < PRINTBLOCK; i++) {
	blockper = (blocks[i]/block)*100;
	if ((blockper > 75) && (blockper <= 100))
	    printf("[#]");
	else if ((blockper > 25) && (blockper <= 75))
	    printf("[-]");
	else if ((blockper >= 0) && (blockper <= 25))
	    printf("[ ]");
    }
    printf("\n");

}
