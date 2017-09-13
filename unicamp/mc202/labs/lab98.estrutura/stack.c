#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

stack_t * st_create() {
    stack_t * s = calloc(1, sizeof(stack_t));
    return s;
}

void st_destroy(stack_t *s) {
    if (s == NULL)
	return;

    while (st_pop(s) != ERR_STACK_NULL);
}

int st_pop(stack_t *s) {
    if (s == NULL)
	return ERR_STACK_NULL;
    if (s->top == NULL)
	return ERR_STACK_NULL;

    int data;
    st_node_t *p = s->top;
    s->top = p->next;
    s->len--;
    data = p->id;
    free(p);
    return data;
}

int st_push(stack_t *s, int data) {
    if (s == NULL)
	return ERR_STACK_NULL;

    st_node_t * node = calloc(1, sizeof(st_node_t));
    if (node == NULL)
	return ERR_NULL_DATA;

    node->next = s->top;
    node->id = data;
    s->top = node;
    s->len++;

    return SUCCESS;
}
int st_len(stack_t *s) {
    if (s == NULL)
	return ERR_STACK_NULL;

    return s->len;
}

void st_print(stack_t *s) {
    if (s == NULL)
	return;
    if (s->top == NULL)
	return;

    st_node_t *p = s->top;
    int i = s->len;;

    while (p != NULL) {
	printf("[I%d]-[data%d] ", i--, p->id);
	p = p->next;
    }
    printf("\n");
}
