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

    int pos = (c->head + c->len) % c->max;

    c->array[pos] = data;

    if (c->len == c->max)
	c->head++;

    else if (c->len < c->max)
	c->len++;

    return SUCCESS;
}

int cv_get(cvector_t *c) {
    if (c == NULL)
	return ERR_VECTOR_NULL;
    if (c->array == NULL)
	return ERR_VECTOR_NULL;
    if (c->len <= 0)
	return ERR_VECTOR_EMPTY;

    int data = c->array[c->head%c->max];

    c->array[c->head%c->max] = 0;

    c->len--;
    c->head++;

    return data;
}

int cv_len(cvector_t *c) {
    if (c == NULL)
	return ERR_VECTOR_NULL;

    return c->len;
}

void cv_print(cvector_t *c, char *msg) {
    if (c == NULL)
	return;
    if (c->array == NULL)
	return;
    if (msg != NULL)
	printf("%s",msg);

    int i = 0;
    if (c->len > 0)
	printf(" ");

    while (i < c->len) {
	printf("%d", c->array[(i+c->head)%c->max]);
	i++;
	if (i < c->len)
	    printf(", ");
    }
    printf("\n");
}

void cv_write_output(FILE *ofd, cvector_t *c, char *msg) {
    if (ofd == NULL)
	return;
    if (c == NULL)
	return;
    if (c->array == NULL)
	return;
    if (msg != NULL)
	fprintf(ofd, msg);

    int i = 0;
    if (c->len > 0)
	fprintf(ofd, " ");

    while (i < c->len) {
	fprintf(ofd, "%d", c->array[(i+c->head)%c->max]);
	i++;
	if (i < c->len)
	    fprintf(ofd, ", ");
    }

    fprintf(ofd,"\n");
}