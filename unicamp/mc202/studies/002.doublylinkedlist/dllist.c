#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "dllist.h"
#include "trace.h"

#define ELEMENTS 6

int32_t main(int32_t argc, char **argv) {
    int32_t i, iindex;
    time_t t;
    /* Inicializa um gerador de numero randomico */
    srand((unsigned) time(&t));


    dllist *l1 = dl_create();

    printf("------------------------------------\n");
    printf("\t\tInserindo\n");
    printf("------------------------------------\n");
    for (i = 0; i < ELEMENTS; i++) {
	switch (1) {
	    case 0:
		printf("--> Inserindo no fim da fila\n");
		break;
	    case 1:
		printf("--> Inserindo no inicio da fila\n");
		dl_insert_beginning(l1, i);
		break;
	    case 2:
		iindex = rand() % i;
		printf("--> Inserindo depois de %d\n", iindex);
		dl_insert_after(l1, iindex, i);
		break;
	    case 3:
		iindex = rand() % i;
		printf("--> Inserindo antes de %d\n", iindex);
		dl_insert_before(l1, iindex, i);
		break;
	}
    }

    printf("------------------------------------\n");
    printf("\t\tRemovendo\n");
    printf("------------------------------------\n");
    for (i = 0; i < ELEMENTS+10; i++) {
	switch (1) {
	    case 0:
		printf("--> Removendo do Inicio da lista\n");
		dl_remove_beginning(l1);
		break;
	    case 1:
		printf("--> Removendo do fim da lista\n");
		dl_remove_end(l1);
		break;
	}
    }
    printf("------------------------------------\n");
    printf("\t\tDestruindo\n");
    printf("------------------------------------\n");


    dl_destroy(&l1);
}

dllist *dl_create() {
    dllist *l = calloc(1, sizeof(dllist));
    return l;
}

int8_t dl_destroy(dllist **l) {
    if (*l == NULL)
	return ERR_NO_LIST;
    if ((*l)->first == NULL)
	return ERR_EMPTY_LIST;

    node *p = (*l)->first;

    while (p != NULL) {
	dl_print(*l, "Antes :", 0, 0);
	(*l)->first = p->next;
	free(p);
	p = (*l)->first;
	dl_print(*l, "Depois:", -1, 0);
    }

    (*l)->last = NULL;
    *l = NULL;

    return SUCCESS;
}

void dl_print(dllist *l, char *headermsg, int32_t index, int8_t reverse) {
    if (l == NULL)
	return;
    if (headermsg != NULL)
	printf("%s%s%s ",ANSI_COLOR_RED, headermsg, ANSI_COLOR_RESET);

    int32_t i = 0;
    node *p = NULL;

    if (reverse) {
	p = l->last;
	printf("NULL");
	while (p != NULL) {
	    printf("%s->", ANSI_COLOR_RED);
	    if (index == i) {
		printf("%s", ANSI_COLOR_YELLOW);
	    } else {
		printf("%s", ANSI_COLOR_GREEN);
	    }
	    printf("[P|I%d|V%d|N]", p->id, p->data);
	    printf("%s<-%s",ANSI_COLOR_RED, ANSI_COLOR_RESET);
	    p = p->prev;
	    i++;
	}
    } else {
	p = l->first;
	printf("NULL");
	while (p != NULL) {
	    printf("%s->", ANSI_COLOR_RED);
	    if (index == i) {
		printf("%s", ANSI_COLOR_YELLOW);
	    } else {
		printf("%s", ANSI_COLOR_GREEN);
	    }
	    printf("[P|I%d|V%d|N]", p->id, p->data);
	    printf("%s<-%s",ANSI_COLOR_RED, ANSI_COLOR_RESET);
	    p = p->next;
	    i++;
	}
    }
    printf("NULL\n");
}

int8_t dl_insert_beginning(dllist *l, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->last_id++;
    nn->data = value;
    nn->prev = NULL;

    node *p = l->first;

    if (p == NULL) {
	l->last = nn;
    } else {
	nn->next = p;
	p->prev = nn;
    }
    l->first = nn;
    l->len++;
    dl_print(l, "Depois:", 0, 0);

    return SUCCESS;
}

int8_t dl_insert_end(dllist *l, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->last_id++;
    nn->data = value;
    node *p = l->last;

    if (l->first == NULL) {
	l->first = nn;
	l->last = nn;
    } else {
	p->next = nn;
	nn->prev = p;
	l->last = nn;
    }
    l->len++;

    dl_print(l, "Depois:", l->len-1, 0);

    return 0;
}

int8_t dl_insert_after(dllist *l, int32_t key, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->last_id++;
    nn->data = value;

    node *p = l->first;
    int32_t i = 0;

    while (p != NULL) {
	if (p->data == key) {
	    nn->next = p->next;
	    p->next = nn;
	    nn->prev = p;
	    if (p == l->last) {
		l->last = nn;
	    }
	    break;
	}
	p = p->next;
	i++;
    }

    dl_print(l, "Depois:", i+1, 0);

    return 0;
}

int8_t dl_insert_before(dllist *l, int32_t key, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->last_id++;
    nn->data = value;

    node *p = l->first;
    int32_t i = 0;

    while (p != NULL) {
	if (p->data == key) {
	    if (p == l->first) {
		l->first = nn;
	    } else {
		p->prev->next = nn;
	    }
	    nn->next = p;
	    nn->prev = p->prev;

	    break;
	}
	i++;
	p = p->next;
    }

    dl_print(l, "Depois:", i, 0);

    return 0;
}

int8_t dl_remove_beginning(dllist *l) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->first;

    dl_print(l, "Antes :", 0, 0);
    l->first = p->next;
    p->next = NULL;

    free(p);

    l->len--;

    dl_print(l, "Depois:", -1, 0);

    return 0;
}

int8_t dl_remove_end(dllist *l) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->last;

    dl_print(l, "Antes :", l->len-1, 0);
    if (p == l->first) {
	l->first = NULL;
    } else {
	p->prev->next = NULL;
	l->last = p->prev;
    }

    free(p);

    l->len--;

    dl_print(l, "Depois:", -1, 0);

    return 0;

}

int8_t dl_remove_next(dllist *l, int32_t key) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->first;
    int32_t i = 0;

    while (p->next != NULL) {
	if (p->data == key) {
	    if (p->next == l->last) {
		l->last = p;
	    } else {
	    }
	}
	p = p->next;
    }
}
int8_t dl_remove_prev(dllist *l, int32_t id);
int8_t dl_remove_all_values(dllist *l, int32_t value);
int8_t dl_remove(dllist *l, int32_t id);

node *dl_get_node(dllist *l, int32_t value);
