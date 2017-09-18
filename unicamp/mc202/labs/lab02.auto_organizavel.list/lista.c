#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lista.h"

void imprimir_list(list *l) {
    if (l == NULL)
	return;

    no *p = l->init;

    while (p!=NULL) {
	printf("%d ", p->valor);
	p = p->prox;
    }
    printf("\n");

    p = l->init;

    while (p!=NULL) {
	printf("%d ", p->acesso);
	p = p->prox;
    }
}

void inserir_lista(list *l, int32_t dado) {
    if (l == NULL)
	return;

    no *novodado = calloc(1,sizeof(no));
    novodado->valor = dado;

    if (l->init == NULL) {
	l->init = novodado;
    } else {
	novodado->prox = l->init;
	l->init = novodado;
    }
}

int32_t req_move_to_front(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int c = 1;

    no *pp = l->init;
    no *p = pp->prox;

    if (l->init->valor == dado) {
	l->init->acesso++;
	return 1;
    }

    while (p != NULL) {
	if (p->valor == dado) {
	    pp->prox = p->prox;
	    p->prox = l->init;
	    l->init = p;
	    ++c;
	    return c;
	}
	pp = p;
	p = pp->prox;
	++c;
    }

    return 0;

}

int32_t req_transpose(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int32_t c = 1;
    no *pp = l->init;
    no *ppp = l->init;
    no *p = pp->prox;

    if (l->init->valor == dado) {
	p->acesso++;
	return c;
    }

    while (p != NULL) {
	if (p->valor == dado) {
	    ppp->prox = pp->prox;
	    pp->prox = p->prox;
	    p->prox = pp;
	    if (l->init == pp) {
		l->init = p;
	    }
	    ++c;
	    return c;
	}
	ppp = pp;
	pp = p;
	p = pp->prox;
	++c;
    }

    return 0;
}

int32_t req_count(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int32_t c = 1;
    no *p = l->init->prox;
    no *pp = l->init;
    no *paux = l->init;

    if (l->init->valor == dado) {
	l->init->acesso++;
	return c;
    }

    while (p != NULL) {
	if (p->valor == dado) {
	    ++c;
	    pp->prox = p->prox;
	    p->prox = NULL;
	    p->acesso++;
	    break;
	}
	pp = p;
	p = p->prox;
	++c;
    }

    while (paux != NULL) {
	if (p->acesso >= paux->acesso) {
	    p->prox = paux;
	    if (paux == l->init)
		l->init = p;
	    else
		pp->prox = p;
	    break;
	}
	pp = paux;
	paux = pp->prox;
    }

    return c;
}