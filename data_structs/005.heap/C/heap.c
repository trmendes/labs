#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "heap.h"

#define HEAP_PARENT(X) ( ( X - 1 ) >> 1 )
#define HEAP_LEFT(X)   ( ( X << 1 ) + 1 )
#define HEAP_RIGHT(X)  ( ( X << 1 ) + 2 )

void hp_heapfy_down(heap_t * heap);
void hp_heapfy_up(heap_t * heap);

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

    memset(heap->heap, 0x00, sizeof(*(heap->heap)));
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

    ++heap->mark;

    hp_heapfy_up(heap);

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

void * hp_get(heap_t * heap) {
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

    hp_heapfy_down(heap);

    return data;
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

void hp_heapfy_up(heap_t * heap) {
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
    int32_t mark = heap->mark - 1;

    int32_t p = HEAP_PARENT(mark);
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
	    if (heap->api.compare(htree[r], htree[p]) > 0) {
		tmp = htree[p];
		htree[p] = htree[r];
		htree[r] = tmp;
	    }
	}

	p = HEAP_PARENT(p);
	l = HEAP_LEFT(p);
	r = HEAP_RIGHT(p);
    }
}

void hp_heapfy_down(heap_t * heap) {
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

    int32_t p = 0;
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
	    }
	}
	l = HEAP_LEFT(p);
	r = HEAP_RIGHT(p);
    }
}
