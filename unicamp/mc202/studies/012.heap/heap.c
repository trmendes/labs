#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "heap.h"

heap_ctrl_t * hp_create(size_t size) {
    heap_ctrl_t * h = (heap_ctrl_t *) calloc(1, sizeof(heap_ctrl_t));
    h->array = (data_t **) calloc(size, sizeof(data_t *));
    h->size = size;
    return h;
}

int32_t hp_insert_max(heap_ctrl_t * heap, int32_t data) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    if (heap->next == heap->size - 1)
	return ERR_HEAP_FULL;

    int32_t parent, leaf;
    data_t * datas = (data_t *) calloc(1, sizeof(data_t));
    datas->data = data;

    heap->array[heap->next] = datas;
    parent = heap->next;
    leaf = heap->next;

    while (parent != 0) {
	if (parent % 2 == 0)
	    parent = (parent - 2) / 2;
	else
	    parent = (parent - 1) / 2;

	if (heap->array[parent]->data <= data) {
	    heap->array[leaf] = heap->array[parent];
	    heap->array[parent] = datas;
	    leaf = parent;
	}
    }
    ++heap->next;

    return SUCCESS;
}

int32_t hp_insert_min(heap_ctrl_t * heap, int32_t data) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    if (heap->next == heap->size - 1)
	return ERR_HEAP_FULL;

    int32_t parent, leaf;
    data_t * datas = (data_t *) calloc(1, sizeof(data_t));
    datas->data = data;

    heap->array[heap->next] = datas;
    parent = heap->next;
    leaf = heap->next;

    while (parent != 0) {
	if (parent % 2 == 0)
	    parent = (parent - 2) / 2;
	else
	    parent = (parent - 1) / 2;

	if (heap->array[parent]->data >= data) {
	    heap->array[leaf] = heap->array[parent];
	    heap->array[parent] = datas;
	    leaf = parent;
	}
    }
    ++heap->next;

    return SUCCESS;
}

int32_t hp_remove_max(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    if (heap->next == 0)
	return ERR_HEAP_EMPTY;

    if (heap->array[0] != (data_t *) NULL)
	free(heap->array[0]);

    --heap->next;
    heap->array[0] = heap->array[heap->next];
    heap->array[heap->next] = (data_t *) NULL;

    hp_heapfy_max(heap);

    return SUCCESS;
}

int32_t hp_remove_min(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    if (heap->next == 0)
	return ERR_HEAP_EMPTY;

    if (heap->array[0] != (data_t *) NULL)
	free(heap->array[0]);

    --heap->next;
    heap->array[0] = heap->array[heap->next];
    heap->array[heap->next] = (data_t *) NULL;

    hp_heapfy_min(heap);

    return SUCCESS;
}

int32_t hp_heapfy_max(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    size_t l, r;
    data_t * tmp;
    int32_t parent = 0;

    while (1) {
	l = LEFT(parent);
	r = RIGHT(parent);
	if (heap->array[r] == (data_t *) NULL) {
	    if (heap->array[l] == (data_t *) NULL)
		break;
	    if (heap->array[l]->data >= heap->array[parent]->data) {
		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	     } else {
		break;
	    }
	} else {
	    if ((heap->array[l]->data >= heap->array[parent]->data) && (heap->array[l]->data > heap->array[r]->data)) {
		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	    } else if ((heap->array[r]->data >= heap->array[parent]->data) && (heap->array[r]->data > heap->array[l]->data)) {
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

int32_t hp_heapfy_min(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    size_t l, r;
    data_t * tmp;
    int32_t parent = 0;

    while (1) {
	l = LEFT(parent);
	r = RIGHT(parent);
	if (heap->array[r] == (data_t *) NULL) {
	    if (heap->array[l] == (data_t *) NULL)
		break;
	    if (heap->array[l]->data < heap->array[parent]->data) {
		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	    } else {
		break;
	    }
	} else {
	    if ((heap->array[l]->data <= heap->array[parent]->data) && (heap->array[l]->data < heap->array[r]->data)) {
		tmp = heap->array[l];
		heap->array[l] = heap->array[parent];
		heap->array[parent] = tmp;
		parent = l;
	    } else if ((heap->array[r]->data <= heap->array[parent]->data) && (heap->array[r]->data < heap->array[l]->data)) {
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

int32_t hp_sort(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;

    data_t ** sorted = (data_t **) calloc(heap->size, sizeof(data_t *));

    int32_t i;

    for (i = (heap->next - 1); i >= 0; --i) {
	sorted[i] = heap->array[0];
	heap->array[0] = heap->array[i];
	heap->array[i] = (data_t *) NULL;

	hp_heapfy_max(heap);
    }

    for (i = 0; i < (int32_t) heap->next; ++i)
	heap->array[i] = sorted[i];

    free(sorted);

    return SUCCESS;
}

int32_t hp_get_head(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return ERR_HEAP_NULL;
    if (heap->next == 0)
	return ERR_HEAP_EMPTY;

    return heap->array[0]->data;
}

void hp_print(heap_ctrl_t * heap) {
    if (heap == (heap_ctrl_t *) NULL)
	return;

    size_t i;

    printf("[");
    for (i = 0; i < heap->next + 1; ++i) {
	if (heap->array[i] != (data_t *) NULL)
	    printf("%d ", heap->array[i]->data);
    }
    printf("]\n");
}
