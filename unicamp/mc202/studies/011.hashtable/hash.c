#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

heap_t * hp_create(int32_t heapsize) {
    heap_t * h = (heap_t *) calloc(1, sizeof(heap_t));
    h->heapsize = heapsize;
    h->array = (node_t **) calloc(heapsize, sizeof(node_t *));
    return h;
}

void hp_destroy(heap_t ** heap) {
    if (*heap == (heap_t *) NULL)
	return;

    int32_t i;
    node_t * p, *pp;

    for (i = 0; i < (*heap)->heapsize; ++i) {
	p = (*heap)->array[i];
	pp = p;
	while (p != (node_t *) NULL) {
	    p = pp->next;
	    printf("Remove %d\n", pp->data.data);
	    free(pp);
	    pp = p;
	}
    }

    free((*heap)->array);
    free(*heap);
    *heap = NULL;
}

int8_t hp_insert_key(heap_t * heap, int32_t data) {
    if (heap == (heap_t *) NULL)
	    return ERR_HEAP_NULL;

    node_t * node = (node_t *) NULL, * p = (node_t *) NULL;
    int32_t index = hp_calc_hash_key(heap, data);

    if (index < 0)
	return index;

    int32_t i = 0;
    node = (node_t *) calloc(1, sizeof(node_t));
    node->data.data = data;

    if (heap->array[index] == (node_t *) NULL) {
	heap->array[index] = node;
	printf("[INSERT] | index: %d | subindex %d | [data %d]\n", index, i, data);
    } else {
	++i;
	p = (node_t *) heap->array[index];
	while (p->next != (node_t *) NULL) {
	    p = p->next;
	    ++i;
	}
	p->next = node;
	printf("[INSERT] | index: %d | subindex %d | [data %d] - [COLLISION]\n", index, i,
		data);
    }

    return SUCCESS;
}

int32_t hp_calc_hash_key(heap_t * heap, int32_t data) {
    if (heap == (heap_t *) NULL)
	    return ERR_HEAP_NULL;

    return data % heap->heapsize;
}

void hp_find_key( heap_t * heap, int32_t data) {
    if (heap == (heap_t *) NULL)
	    return;

    int32_t index = hp_calc_hash_key(heap, data);
    int32_t i = 0;
    node_t * node = (node_t *) NULL;

    if (index < 0)
	return;

    node = heap->array[index];

    if (node != (node_t *) NULL) {
	while (node != (node_t *) NULL) {
	    if (node->data.data == data) {
		printf("Data found at heap index %d | subindex %d\n", index, i);
		break;
	    }
	    ++i;
	    node = node->next;
	}
    }

    if (node == (node_t *) NULL)
	printf("[ERR] data %d not found\n", data);

}
