#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "dllist.h"
#include "trace.h"

dllist *dl_create() {
    dllist *l = (dllist *) calloc(1, sizeof(dllist));
    return l;
}

int8_t dl_destroy(dllist **l) {
    if (*l == (dllist *) NULL)
	return ERR_NO_LIST;
    if ((*l)->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *p = (*l)->head;

    while (p != (node *) NULL) {
	(*l)->head = p->next;
	free(p);
	p = (*l)->head;
    }

    (*l)->tail = (node *) NULL;
    *l = (dllist *) NULL;

    return SUCCESS;
}

void dl_print(dllist *l, char *headermsg, int32_t index, int8_t reverse) {
    if (l == (dllist *) NULL)
	return;
    if (headermsg != (char *) NULL)
	printf("%s%s%s ",ANSI_COLOR_RED, headermsg, ANSI_COLOR_RESET);

    int32_t i = 0;
    node *p = (node *) NULL;

    if (reverse) {
	p = l->tail;
	printf("NULL");
	while (p != (node *) NULL) {
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
	while (p != (node *) NULL) {
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
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;

    node *nn = (node *) calloc(1, sizeof(node));

    if (nn == (node *) NULL)
	return ERR_MALLOC_FAIL;

    nn->id = l->tail_id++;
    nn->data = value;
    nn->prev = (node *) NULL;

    node *p = l->head;

    if (p == (node *) NULL) {
	l->tail = nn;
    } else {
	nn->next = p;
	p->prev = nn;
    }
    l->head = nn;
    l->len++;

    return SUCCESS;
}

int8_t dl_insert_tail(dllist *l, int32_t value) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;

    node *nn = (node *) calloc(1, sizeof(node));

    if (nn == (node *) NULL)
	return ERR_MALLOC_FAIL;

    nn->id = l->tail_id++;
    nn->data = value;
    node *p = l->tail;

    if (l->head == (node *) NULL) {
	l->head = nn;
	l->tail = nn;
    } else {
	p->next = nn;
	nn->prev = p;
	l->tail = nn;
    }
    l->len++;

    return SUCCESS;
}

int8_t dl_insert_after(dllist *l, int32_t key, int32_t value) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *nn = (node *) calloc(1, sizeof(node));

    if (nn == (node *) NULL)
	return ERR_MALLOC_FAIL;

    nn->id = l->tail_id++;
    nn->data = value;

    node *p = l->head;

    while (p != (node *) NULL) {
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
    }

    return SUCCESS;
}

int8_t dl_insert_before(dllist *l, int32_t key, int32_t value) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *nn = (node *) calloc(1, sizeof(node));

    if (nn == (node *) NULL)
	return ERR_MALLOC_FAIL;

    nn->id = l->tail_id++;
    nn->data = value;

    node *p = l->head;

    while (p != (node *) NULL) {
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
	p = p->next;
    }

    return SUCCESS;
}

int8_t dl_remove_beginning(dllist *l) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *p = l->head;

    l->head = p->next;
    p->next = (node *) NULL;

    free(p);

    l->len--;

    return SUCCESS;
}

int8_t dl_remove_tail(dllist *l) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *p = l->tail;

    if (p == l->head) {
	l->head = (node *) NULL;
    } else {
	p->prev->next = (node *) NULL;
	l->tail = p->prev;
    }

    free(p);

    l->len--;

    return SUCCESS;

}

int8_t dl_remove_next(dllist *l, int32_t key) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *p = l->head;
    node *r = (node *) NULL;

    while (p->next != (node *) NULL) {
	if (p->id == key) {
	    r = p->next;

	    if (r->next == (node *) NULL) {
		l->tail = p;
		p->next = (node *) NULL;
	    } else {
		r->next->prev = p;
		p->next = r->next;
	    }

	    free(r);
	    l->len--;
	    r = (node *) NULL;
	    break;
	}
	p = p->next;
    }

    return SUCCESS;
}

int8_t dl_remove_prev(dllist *l, int32_t key) {
    if (l == (dllist *) NULL)
	return ERR_NO_LIST;
    if (l->head == (node *) NULL)
	return ERR_EMPTY_LIST;

    node *p = l->head->next;
    node *r = (node *) NULL;

    while (p != (node *) NULL) {
	if (p->id == key) {
	    r = p->prev;
	    if (r == l->head) {
		l->head = p;
		p->prev = (node *) NULL;
	    } else {
		p->prev = r->prev;
		r->prev->next = p;
	    }
	    free(r);
	    l->len--;
	    r = (node *) NULL;
	    break;
	}
	p = p->next;
    }

    return SUCCESS;
}
