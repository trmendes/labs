#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "dvector.h"
#include "trace.h"

dvector * dv_create(int32_t size) {
    dvector *v = (dvector *) calloc(1, sizeof(dvector));
    if (v == (dvector *) NULL)
	goto RETURN;
    v->array = (int32_t *) calloc(size, sizeof(int32_t));

    if (v->array == (int32_t *) NULL) {
	free(v);
    }

    v->alloc_cnt++;
    v->size = size;
    v->orsize = size;
    v->head_idx = size - 1;

RETURN:
    return v;
}

int8_t dv_realloc(dvector *v) {
    if (v == (dvector *) NULL)
	return ERR_NO_VECTOR;

    int32_t ns = v->size + v->orsize;
    int32_t * nv = calloc(ns, sizeof(int32_t));

    if (nv == (int32_t *) NULL)
	return ERR_CANT_EXPAND;

    for (int32_t i = 0, j = v->head_idx+1; i < v->len; i++, j++) {
	nv[(j+v->orsize)%ns] = v->array[(j)%v->size];
    }
    printf("\n");

    free(v->array);
    v->array = nv;
    v->head_idx = v->head_idx + v->orsize;
    v->alloc_cnt++;
    v->size = ns;
    dv_print_array_info(v);

    return SUCCESS;
}

void dv_destroy(dvector *v) {
    if (v == (dvector *) NULL)
	return;
    if (v->array)
	free(v->array);
    free(v);
}

int8_t dv_insert_head(dvector *v, int32_t value) {
    if (v == (dvector *) NULL)
	return ERR_NO_VECTOR;

    if (v->array == (int32_t *) NULL)
	return ERR_NO_ARRAY;

    if (v->size == v->len) {
	if (dv_realloc(v) == ERR_CANT_EXPAND)
	    return ERR_CANT_EXPAND;
    }

    v->array[v->head_idx] = value;
    v->len++;
    v->head_idx--;

    return SUCCESS;
}

int8_t dv_remove_head(dvector *v) {
    if (v == (dvector *) NULL)
	return ERR_NO_VECTOR;

    if (v->array == (int32_t *) NULL)
	return ERR_NO_ARRAY;

    if (v->len <= 0)
	return EMPTY_ARRAY;

    if (v->head_idx >= v->size - 1)
	return NO_HEAD;

    v->len--;
    v->head_idx++;
    v->array[v->head_idx] = 0;

    return SUCCESS;
}

int8_t dv_insert_tail(dvector *v, int32_t value) {
    if (v == (dvector *) NULL)
	return ERR_NO_VECTOR;

    if (v->array == (int32_t *) NULL)
	return ERR_NO_ARRAY;

    if (v->size == v->len) {
	if (dv_realloc(v) == ERR_CANT_EXPAND)
	    return ERR_CANT_EXPAND;
    }

    int32_t pos = ((v->head_idx + 1) + v->len) % v->size;

    v->array[pos] = value;
    v->len++;

    return SUCCESS;
}

int8_t dv_remove_tail(dvector *v) {
    if (v == (dvector *) NULL)
	return ERR_NO_VECTOR;

    if (v->array == (int32_t *) NULL)
	return ERR_NO_ARRAY;

    if (v->len <= 0)
	return EMPTY_ARRAY;

    int32_t pos = (((v->head_idx + 1) + v->len) % v->size) -1;

    if (pos <= -1)
	return NO_TAIL;

    v->len--;
    v->array[pos] = 0;

    return SUCCESS;
}

void dv_print_array_info(dvector *v) {
    if (v == (dvector *) NULL)
	return;
    if (v->array == (int32_t *) NULL)
	return;

    printf("\n-----------------------------------------------------\n");
    printf("-> Tamanho inicial: %d\n", v->orsize);
    printf("-> Tamanho agora  : %d\n", v->size);
    printf("-> Realocacoes    : %d\n", v->alloc_cnt);
    printf("-----------------------------------------------------\n");
}

void dv_print(dvector *v, char *head) {
    if (v == (dvector *) NULL)
	return;
    if (v->array == (int32_t *) NULL)
	return;

    if (head != (char *) NULL)
	printf("%s%s%s\n", ANSI_COLOR_RED, head, ANSI_COLOR_RESET);

    int32_t tail_idx = (((v->head_idx + 1) + v->len) % v->size) - 1;

    printf("[%s[tail]%s[head]%s]:[SIZE %d|LEN %d|T_IDX %d|H_IDX %d]\n> [", ANSI_COLOR_GREEN, ANSI_COLOR_MAGENTA, ANSI_COLOR_RESET, v->size, v->len, tail_idx, v->head_idx);

    for (int32_t i = 0; i < v->size; i++) {
	if (i > v->head_idx) {
	    if (i-1 == v->head_idx)
		printf(" %s%d%s ",ANSI_COLOR_MAGENTA, v->array[i], ANSI_COLOR_RESET);
	    else 
		printf(" %d ", v->array[i]);
	} else {
	    if ((i == tail_idx) || ((i == tail_idx) && (i == 0)))
		printf(" %s%d%s ",ANSI_COLOR_GREEN, v->array[i], ANSI_COLOR_RESET);
	    else
		printf(" %d ", v->array[i]);
	}
    }
    printf("]\n");

}