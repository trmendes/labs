#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>
#include <stdlib.h>
#include "bintree.h"

#define ERR_NO_KEY     -5
#define ERR_REPT_KEY   -4
#define ERR_HEAP_EMPTY -3
#define ERR_HEAP_FULL  -2
#define ERR_HEAP_NULL  -1
#ifndef SUCCESS
#define SUCCESS         EXIT_SUCCESS
#endif

#define LEFT(N)  ( (2 * N) + 1 )
#define RIGHT(N) ( (2 * N) + 2 )

typedef struct data_s {
    int32_t price;
    int32_t key;
} data_t;

typedef struct heap_ctrl_s {
    data_t      ** array;
    leaf_t       * map;
    size_t         size;
    uint32_t       next;
} heap_ctrl_t;

heap_ctrl_t * hp_create            (size_t size);
void          hp_destroy           (heap_ctrl_t ** heap);
int32_t       hp_insert_min        (heap_ctrl_t * heap, int32_t key, int32_t pri);
data_t *      hp_remove_min        (heap_ctrl_t * heap);
int32_t       hp_heapify_botton_up (heap_ctrl_t * heap, int32_t parent);
int32_t       hp_heapify_top_down  (heap_ctrl_t * heap, int32_t parent);
data_t *      hp_get_head          (heap_ctrl_t * heap);
int32_t       hp_change_pri        (heap_ctrl_t * heap, int32_t key, int32_t new_pri);
int32_t       hp_sort              (heap_ctrl_t * heap);
void          hp_print             (heap_ctrl_t * heap);
#endif