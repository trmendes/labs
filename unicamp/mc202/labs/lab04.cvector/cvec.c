#include "cvec.h"
#include <stdlib.h>
#include <stdio.h>

cvector_t * cv_create(int size) {
    cvector_t * a = calloc(1, sizeof(cvector_t));
    if (a != NULL) {
	a->array = calloc(size, sizeof(int));
	a->max = size;
    }

    return a;
}

int cv_destroy(cvector_t **c) {
    if (*c == NULL)
	return ERR_VECTOR_NULL;

    if ((*c)->array != NULL)
	free((*c)->array);

    free(*c);

    *c = NULL;

    return SUCCESS;
}

int cv_insert(cvector_t *c, int data) {
    if (c == NULL)
	return ERR_VECTOR_NULL;

    if (c->array == NULL)
	return ERR_VECTOR_NULL;

    int pos = c->head % c->max;
    c->array[pos] = data;

    if (c->len < (c->max - 1))
	c->len++;

    c->head++;

    return SUCCESS;
}

int cv_get(cvector_t *c) {
    if (c == NULL)
	return ERR_VECTOR_NULL;
    if (c->array == NULL)
	return ERR_VECTOR_NULL;
    if (c->len <= 0)
	return ERR_VECTOR_EMPTY;

    int pos = c->max - (c->len + 1);
    int data = c->array[pos];

    //FIXME: Arrumar aqui e o LEN
    c->array[pos] = 0;
    
    c->len--;
    

    return data;
}

int cv_len(cvector_t *c) {
    if (c == NULL)
	return ERR_VECTOR_NULL;

    return c->len - 1;
}

void cv_print(cvector_t *c) {
    if (c == NULL)
	return;
    if (c->array == NULL)
	return;

    int i = c->len;
    while (i >= 0) {
	printf("%d, ", c->array[i]);
	i--;
    }
    printf("\b\b ");
}