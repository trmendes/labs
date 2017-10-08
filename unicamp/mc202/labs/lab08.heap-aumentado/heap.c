#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "heap.h"

heap_ctrl_t * hp_create(size_t size) {
    heap_ctrl_t * h = (heap_ctrl_t *) calloc(1, sizeof(heap_ctrl_t));
    h->array = (data_t **) calloc(size, sizeof(data_t *));
    h->map = tr_create();
    h->size = size;
    return h;
}

void hp_destroy(heap_ctrl_t ** heap) {
    if (*heap == (heap_ctrl_t *) NULL)
	return;

    int32_t i;

    for (i = 0; i < (int32_t) (*heap)->size; ++i) {
	if ((*heap)->array[i] != (data_t *) NULL)
	    free((*heap)->array[i]);
    }

    free((*heap)->array);
    tr_destroy((*heap)->map);
    free(*heap);
    *heap = (heap_ctrl_t *) NULL;
}

int32_t hp_insert_min(heap_ctrl_t * heap, int32_t key, int32_t pri) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    if (heap->next == heap->size - 1)
	return ERR_HEAP_FULL;

    int32_t i;

    i = tr_find_get_key_idx(heap->map, key);
    if (i != ERR_NO_LEAF)
	return ERR_REPT_KEY;

    data_t * data = (data_t *) calloc(1, sizeof(data_t));
    data->price = pri;
    data->key = key;

    tr_insert_by_value(&heap->map, key, heap->next);
    heap->array[heap->next] = data;

    hp_heapify_botton_up(heap, heap->next);

   ++heap->next;

    return SUCCESS;
}

data_t * hp_remove_min(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return NULL;

    if (heap->next == 0)
	return NULL;

    data_t *tmp = (data_t *) NULL;
    tmp = heap->array[0];

    --heap->next;

    tr_delete(&heap->map, heap->array[0]->key);

    heap->array[0] = heap->array[heap->next];
    heap->array[heap->next] = (data_t *) NULL;

    hp_heapify_top_down(heap, 0);

    return tmp;
}

int32_t hp_heapify_botton_up(heap_ctrl_t * heap, int32_t parent) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    int32_t leaf = parent;
    int32_t pri = heap->array[parent]->price;
    data_t * tmp = heap->array[parent];

    while (parent != 0) {
	if (parent % 2 == 0)
	    parent = (parent - 2) / 2;
	else
	    parent = (parent - 1) / 2;

	if (heap->array[parent]->price >= pri) {
	    tr_update_idx(heap->map, heap->array[parent]->key, leaf);
	    tr_update_idx(heap->map, heap->array[leaf]->key, parent);

	    heap->array[leaf] = heap->array[parent];
	    heap->array[parent] = tmp;
	    leaf = parent;
	}
    }

    return SUCCESS;
}

int32_t hp_heapify_top_down(heap_ctrl_t * heap, int32_t parent) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    size_t l, r;
    data_t * tmp;

    while (1) {
	l = LEFT(parent);
	r = RIGHT(parent);
	if (heap->array[l] == (data_t *) NULL)
	    break;

	if (heap->array[r] == (data_t *) NULL) {
	    if (heap->array[l]->price < heap->array[parent]->price) {
		tr_update_idx(heap->map, heap->array[parent]->key, l);
		tr_update_idx(heap->map, heap->array[l]->key, parent);

		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	    } else {
		break;
	    }
	} else {
	    if ((heap->array[l]->price <= heap->array[parent]->price) && (heap->array[l]->price < heap->array[r]->price)) {
		tr_update_idx(heap->map, heap->array[parent]->key, l);
		tr_update_idx(heap->map, heap->array[l]->key, parent);

		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	    } else if ((heap->array[r]->price <= heap->array[parent]->price) && (heap->array[r]->price < heap->array[l]->price)) {
		tr_update_idx(heap->map, heap->array[parent]->key, r);
		tr_update_idx(heap->map, heap->array[r]->key, parent);

		tmp = heap->array[r];
		heap->array[r] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = r;
	    } else {
		break;
	    }
	}
    }

    return SUCCESS;
}

int32_t hp_change_pri(heap_ctrl_t * heap, int32_t key, int32_t new_pri) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    int32_t i, ovalue = new_pri;

    i = tr_find_get_key_idx(heap->map, key);

    if ((i < 0) || (i > (int32_t) heap->size))
	return ERR_NO_LEAF;

    if (heap->array[i] == (data_t *) NULL)
	return ERR_NO_LEAF;

    ovalue = heap->array[i]->price;
    heap->array[i]->price = new_pri;

    if (ovalue > new_pri) {
	hp_heapify_botton_up(heap,i);
    } else if (ovalue < new_pri) {
	hp_heapify_top_down(heap, i);
    }

    return SUCCESS;
}

data_t * hp_get_head(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return NULL;
    if (heap->next == 0)
	return NULL;

    return heap->array[0];
}

void hp_print(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return;

    size_t i;

    printf("[");
    for (i = 0; i < heap->next + 1; ++i) {
	if (heap->array[i] != (data_t *) NULL)
	    printf("%d[k%d] ", heap->array[i]->price, heap->array[i]->key);
    }
    printf("]\n");
}
