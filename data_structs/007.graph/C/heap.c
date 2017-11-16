#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "heap.h"

#define HEAP_PARENT(X) ( ( X - 1 ) >> 1 )
#define HEAP_LEFT(X)   ( ( X << 1 ) + 1 )
#define HEAP_RIGHT(X)  ( ( X << 1 ) + 2 )

void hp_heapfy_down (heap_t * heap, int32_t start);
void hp_heapfy_up   (heap_t * heap, int32_t start);

heap_t * hp_init(size_t heap_size, compare_ft compare, print_ft print) {
    if (compare == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return NULL;
    }

    heap_t * heap = calloc(1, sizeof(*heap));

    if (heap == NULL) {
	errno = HEAP_ERR_MALLOC_FAIL;
	return NULL;
    }

    heap->heap = calloc(heap_size, sizeof(*(heap->heap)));

    if (heap->heap == NULL) {
	errno = HEAP_ERR_MALLOC_FAIL;
	memset(heap, 0x00, sizeof(*heap));
	free(heap);
	return NULL;
    }

    heap->api.compare = compare;
    heap->api.print = print;
    heap->size = heap_size;

    errno = HEAP_SUCCESS;
    return heap;
}

void hp_destroy(heap_t * heap, destroy_ft destroy) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    int32_t i;

    if (destroy != NULL) {
	for (i = heap->mark - 1; i >= 0; --i) {
	    if (heap->heap[i] != NULL)
		destroy(&(heap->heap[i]));
	}
    }

    memset(heap->heap, 0x00, heap->size * sizeof(*(heap->heap)));
    free(heap->heap);
    memset(heap, 0x00, sizeof(*heap));
    free(heap);
}

int32_t hp_insert(heap_t * heap, void * data) {
    if ((heap == NULL) || (data == NULL))
	return HEAP_ERR_NULL_PARS;

    if (heap->heap == NULL)
	return HEAP_ERR_NULL_PARS;

    heap->heap[heap->mark] = data;

    hp_heapfy_up(heap, heap->mark);

    ++heap->mark;

    return HEAP_SUCCESS;
}

void * hp_lookup(heap_t * heap) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return NULL;
    }

    if (heap->heap == NULL) {
	errno = HEAP_ERR_DATA_NFOUND;
	return NULL;
    }

    if (heap->heap[0] == NULL) {
	errno = HEAP_ERR_DATA_NFOUND;
    } else {
	errno = HEAP_SUCCESS;
    }

    return heap->heap[0];
}

void * hp_extract(heap_t * heap) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return NULL;
    }

    if (heap->heap == NULL) {
	errno = HEAP_ERR_DATA_NFOUND;
	return NULL;
    }

    if (heap->heap[0] == NULL) {
	errno = HEAP_ERR_DATA_NFOUND;
    } else {
	errno = HEAP_SUCCESS;
    }

    void *data = heap->heap[0];

    --heap->mark;
    heap->heap[0] = heap->heap[heap->mark];
    heap->heap[heap->mark] = NULL;

    hp_heapfy_down(heap, 0);

    return data;
}

int32_t hp_update(heap_t * heap, void * data, void * new_data, update_ft update) {
    if ((heap == NULL) || (data == NULL) || (new_data == NULL) || (update == NULL))
	return HEAP_ERR_NULL_PARS;

    if (heap->heap == NULL)
	return HEAP_ERR_NULL_PARS;

    void * to_update = NULL;
    size_t i;
    int32_t mark = heap->mark - 1;

    for (i = 0; i < heap->size; ++i) {
	if (heap->heap[i] == data) {
	    to_update = heap->heap[i];
	    break;
	}
    }

    if (to_update == NULL)
	return HEAP_ERR_DATA_NFOUND;

    update(to_update, new_data);

    heap->heap[i] = heap->heap[mark];
    heap->heap[mark] = to_update;

    hp_heapfy_up(heap, mark);

    return HEAP_SUCCESS;

}

void hp_print(heap_t * heap) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    if (heap->heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    if (heap->api.print == NULL) {
	errno = HEAP_ERR_API_NULL;
	return;
    }

    int32_t i;

    for (i = 0; i < heap->mark; ++i) {
	heap->api.print(heap->heap[i]);
    }

    printf("\n");
}

void hp_heapfy_up(heap_t * heap, int32_t start) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    if (heap->heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    /* heapead */
    if (heap->mark <= 1)
	return;

    void ** htree = heap->heap;
    void * tmp = NULL;

    int32_t p = HEAP_PARENT(start);
    int32_t l = HEAP_LEFT(p);
    int32_t r = HEAP_RIGHT(p);

    while (p >= 0) {
	if (htree[r] == NULL) {
	    if (htree[l] != NULL) {
		if (heap->api.compare(htree[l], htree[p]) > 0) {
		    tmp = htree[p];
		    htree[p] = htree[l];
		    htree[l] = tmp;
		}
	    }
	} else {
	    if ((heap->api.compare(htree[r], htree[p]) > 0) && (heap->api.compare(htree[r], htree[l]) > 0)) {
		tmp = htree[p];
		htree[p] = htree[r];
		htree[r] = tmp;
	    } else if ((heap->api.compare(htree[l], htree[p]) > 0) && (heap->api.compare(htree[l], htree[r]) > 0)) {
		tmp = htree[p];
		htree[p] = htree[l];
		htree[l] = tmp;
	    }
	}

	p = HEAP_PARENT(p);
	l = HEAP_LEFT(p);
	r = HEAP_RIGHT(p);
    }
}

void hp_heapfy_down(heap_t * heap, int32_t start) {
    if (heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    if (heap->heap == NULL) {
	errno = HEAP_ERR_NULL_PARS;
	return;
    }

    /* heapead */
    if (heap->mark <= 1)
	return;

    void ** htree = heap->heap;
    void * tmp = NULL;

    int32_t p = start;
    int32_t l = HEAP_LEFT(p);
    int32_t r = HEAP_RIGHT(p);

    /* Heap is a complete tree...so if the left leaf is NULL...there is no
     * right leaf */
    while (htree[l] != NULL) {
	if (htree[r] == NULL) {
	    if (heap->api.compare(htree[l], htree[p]) > 0) {
		tmp = htree[p];
		htree[p] = htree[l];
		htree[l] = tmp;
		p = l;
	    } else {
		break;
	    }
	} else {
	    if ((heap->api.compare(htree[l], htree[p]) > 0) && (heap->api.compare(htree[l], htree[r]) > 0)) {
		tmp = htree[p];
		htree[p] = htree[l];
		htree[l] = tmp;
		p = l;
	    }
	    else if ((heap->api.compare(htree[r], htree[p]) > 0) && (heap->api.compare(htree[r], htree[l]) > 0)) {
		tmp = htree[p];
		htree[p] = htree[r];
		htree[r] = tmp;
		p = r;
	    } else {
		break;
	    }
	}
	l = HEAP_LEFT(p);
	r = HEAP_RIGHT(p);

	if (r >= heap->size)
	    break;
    }
}

