#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <stdint.h>

#define HEAP_ERR_API_NULL    -4
#define HEAP_ERR_DATA_NFOUND -3
#define HEAP_ERR_NULL_PARS   -2
#define HEAP_ERR_MALLOC_FAIL -1
#define HEAP_SUCCESS          0

typedef int32_t (*compare_ft) (const void * const data_a, const void * const data_b);
typedef void    (*destroy_ft) (void **data);
typedef void    (*print_ft)   (const void * const data);

typedef struct heap_api_s {
    compare_ft compare;
    print_ft   print;
} heap_api_t;

typedef struct heap_s {
    int32_t       mark;
    void       ** heap;
    heap_api_t    api;
} heap_t;


heap_t * hp_init    (size_t heap_size, compare_ft compare, print_ft print);
void     hp_destroy (heap_t * heap, destroy_ft destroy);
int32_t  hp_insert  (heap_t * heap, void * data);
void   * hp_lookup  (heap_t * heap);
void   * hp_get     (heap_t * heap);
void     hp_print   (heap_t * heap);

#endif