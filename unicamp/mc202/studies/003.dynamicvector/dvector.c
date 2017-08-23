#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "dvector.h"
#include "trace.h"

dvector * dv_create(int32_t size) {
    dvector *v = calloc(1, sizeof(dvector));
    if (v == NULL)
	goto RETURN;
    v->array = calloc(size, sizeof(int32_t));

    if (v->array == NULL) {
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
    if (v == NULL)
	return ERR_NO_VECTOR;

    int32_t nel = v->size + v->orsize;
    int32_t * nv = calloc(nel, sizeof(int32_t));

    if (nv == NULL)
	return ERR_CANT_EXPAND;

    int32_t j = 0;

    for (int32_t i = 0; i < v->len; i++) {
	if (i >= v->head_idx) {
	    nv[nel-j] = v->array[v->len-j];
	    j++;
	}
	if (i <= v->tail_idx) {
	    nv[i] = v->array[i];
	}
    }
    printf("\n");

    free(v->array);
    v->array = nv;
    v->head_idx = nel - j;
    v->alloc_cnt++;
    v->size = nel;
    dv_print_array_info(v);

    return SUCCESS;
}

void dv_destroy(dvector *v) {
    if (v == NULL)
	return;
    if (v->array)
	free(v->array);
    free(v);
}

int8_t dv_insert_head(dvector *v, int32_t value) {
    if (v == NULL)
	return ERR_NO_VECTOR;

    if (v->array == NULL)
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

int8_t dv_insert_tail(dvector *v, int32_t value) {
    if (v == NULL)
	return ERR_NO_VECTOR;

    if (v->array == NULL)
	return ERR_NO_ARRAY;

    if (v->size == v->len) {
	if (dv_realloc(v) == ERR_CANT_EXPAND)
	    return ERR_CANT_EXPAND;
    }

    v->array[v->tail_idx] = value;
    v->len++;
    v->tail_idx++;

    return SUCCESS;
}

void dv_print_array_info(dvector *v) {
    if (v == NULL)
	return;
    if (v->array == NULL)
	return;

    printf("\n-----------------------------------------------------\n");
    printf("-> Tamanho inicial: %d\n", v->orsize);
    printf("-> Tamanho agora  : %d\n", v->size);
    printf("-> Realocacoes    : %d\n", v->alloc_cnt);
    printf("-----------------------------------------------------\n");
}

void dv_print(dvector *v, char *head) {
    if (v == NULL)
	return;
    if (v->array == NULL)
	return;

    if (head != NULL)
	printf("%s%s%s\n", ANSI_COLOR_RED, head, ANSI_COLOR_RESET);

    printf("[%s[tail]%s[head]%s]:[SIZE %d|LEN %d|T_IDX %d|H_IDX %d]\n> [", ANSI_COLOR_GREEN, ANSI_COLOR_MAGENTA, ANSI_COLOR_RESET, v->size, v->len, v->tail_idx, v->head_idx);

    for (int32_t i = 0; i < v->size; i++) {
	if (i > v->head_idx) {
	    if (i-1 == v->head_idx)
		printf(" %s%d%s ",ANSI_COLOR_MAGENTA, v->array[i], ANSI_COLOR_RESET);
	    else 
		printf(" %d ", v->array[i]);
	} else {
	    if ((i == v->tail_idx-1) || ((i == v->tail_idx) && (i == 0)))
		printf(" %s%d%s ",ANSI_COLOR_GREEN, v->array[i], ANSI_COLOR_RESET);
	    else
		printf(" %d ", v->array[i]);
	}
    }
    printf("]\n");

}