#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "dllist.h"
#include "trace.h"

dllist *dl_create() {
    dllist *l = calloc(1, sizeof(dllist));
    return l;
}

int8_t dl_destroy(dllist **l) {
    if (*l == NULL)
	return ERR_NO_LIST;
    if ((*l)->head == NULL)
	return ERR_EMPTY_LIST;

    node *p = (*l)->head;

    while (p != NULL) {
	dl_print(*l, "Antes :", 0, 0);
	(*l)->head = p->next;
	free(p);
	p = (*l)->head;
	dl_print(*l, "Depois:", -1, 0);
    }

    (*l)->tail = NULL;
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
	p = l->tail;
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
	p = l->head;
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
    nn->id = l->tail_id++;
    nn->data = value;
    nn->prev = NULL;

    node *p = l->head;

    if (p == NULL) {
	l->tail = nn;
    } else {
	nn->next = p;
	p->prev = nn;
    }
    l->head = nn;
    l->len++;
    dl_print(l, "Depois:", 0, 0);

    return SUCCESS;
}

int8_t dl_insert_tail(dllist *l, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->tail_id++;
    nn->data = value;
    node *p = l->tail;

    if (l->head == NULL) {
	l->head = nn;
	l->tail = nn;
    } else {
	p->next = nn;
	nn->prev = p;
	l->tail = nn;
    }
    l->len++;

    dl_print(l, "Depois:", l->len-1, 0);

    return 0;
}

int8_t dl_insert_after(dllist *l, int32_t key, int32_t value) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->head == NULL)
	return ERR_EMPTY_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->tail_id++;
    nn->data = value;

    node *p = l->head;
    int32_t i = 0;

    while (p != NULL) {
	if (p->data == key) {
	    nn->next = p->next;
	    p->next = nn;
	    nn->prev = p;
	    if (p == l->tail) {
		l->tail = nn;
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
    if (l->head == NULL)
	return ERR_EMPTY_LIST;

    node *nn = calloc(1, sizeof(node));

    if (nn == NULL)
	return ERR_MALLOC_FAIL;

    dl_print(l, "Antes :", -1, 0);
    nn->id = l->tail_id++;
    nn->data = value;

    node *p = l->head;
    int32_t i = 0;

    while (p != NULL) {
	if (p->data == key) {
	    if (p == l->head) {
		l->head = nn;
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
    if (l->head == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->head;

    dl_print(l, "Antes :", 0, 0);
    l->head = p->next;
    p->next = NULL;

    free(p);

    l->len--;

    dl_print(l, "Depois:", -1, 0);

    return 0;
}

int8_t dl_remove_tail(dllist *l) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->head == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->tail;

    dl_print(l, "Antes :", l->len-1, 0);
    if (p == l->head) {
	l->head = NULL;
    } else {
	p->prev->next = NULL;
	l->tail = p->prev;
    }

    free(p);

    l->len--;

    dl_print(l, "Depois:", -1, 0);

    return 0;

}

int8_t dl_remove_next(dllist *l, int32_t key) {
    if (l == NULL)
	return ERR_NO_LIST;
    if (l->head == NULL)
	return ERR_EMPTY_LIST;

    node *p = l->head;
    int32_t i = 0;

    while (p->next != NULL) {
	if (p->data == key) {
	    if (p->next == l->tail) {
		l->tail = p;
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
