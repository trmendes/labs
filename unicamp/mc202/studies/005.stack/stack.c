#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

stack_t * st_create() {
    stack_t * s = (stack_t *) calloc(1, sizeof(stack_t));
    return s;
}

void st_destroy(stack_t *s) {
    if (s == (stack_t *) NULL)
	return;

    node_t *p;
    while ((p = st_pop(s)) != (node_t *) NULL) {
	free(p);
    }

    s->len = 0;
}

node_t * st_pop(stack_t *s) {
    if (s == (stack_t *) NULL)
	return (node_t *) NULL;
    node_t *p = s->top;
    s->top = p->next;
    s->len--;
    return p;
}

int st_push(stack_t *s, node_t * data) {
    if (s == (stack_t *) NULL)
	return ERR_STACK_NULL;
    if (data == (node_t *) NULL)
	return ERR_NULL_DATA;

    data->next = s->top;
    s->top = data;
    s->len++;

    return SUCCESS;
}
int st_len(stack_t *s) {
    if (s == (stack_t *) NULL)
	return ERR_STACK_NULL;

    return s->len;
}

void st_print(stack_t *s) {
    if (s == (stack_t *) NULL)
	return;
    if (s->top == (node_t *) NULL)
	return;

    node_t *p = s->top;
    int i = s->len;;

    while (p != (node_t *) NULL) {
	printf("[I%d]-[data%d] ", i--, p->id);
	p = p->next;
    }
    printf("\n");
}
