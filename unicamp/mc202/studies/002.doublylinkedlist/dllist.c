#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "dllist.h"
#include "trace.h"

int32_t main(int32_t argc, char **argv) {

}

dllist *dl_create() {
    dllist *l = calloc(1, sizeof(dllist));
    return l;
}

int8_t dl_destory(dllist **l) {
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

void dl_print(dllist *l, char *headermsg, int32_t index, int8_t reverse);

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

    if (l->first != NULL) {
	nn->next = l->first->next;
    } else {
	l->last = nn;
    }

    l->first = p;
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

    if (l->first == NULL) {
	l->first = nn;
    }

    dl_print(l, "Depois:", l->len-1, 0);

    return 0;
}

int8_t dl_insert_after(dllist *l, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->first == NULL)
	return ERR_EMPTY_LIST;

    node *nn = calloc(1, sizeof(node));
    node *p = l->first;

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->last_id++;
    nn->data = value;

    while (p != NULL) {
	if (p->data == value) {
	    if ( p == p->first) {

	    } else if ( p == f->last ) {
	    } else {
	    }
	}
	p = p->next;
    }
}

int8_t dl_insert_before(dllist *l, int32_t value);

int8_t dl_remove_beginning(dllist *l);
int8_t dl_remove_end(dllist *l);
int8_t dl_remove_next(dllist *l, int32_t id);
int8_t dl_remove_prev(dllist *l, int32_t id);
int8_t dl_remove_all_values(dllist *l, int32_t value);
int8_t dl_remove(dllist *l, int32_t id);

node *dl_get_node(dllist *l, int32_t value);

