#ifndef __HASH_H__
#define __HASH_H

#include <stdint.h>

#define ERR_WRONG_DATA -2
#define ERR_HEAP_NULL  -1
#define SUCCESS         0

typedef struct data_s {
    int32_t data;
} data_t;

typedef struct node_s {
    data_t          data;
    struct node_s * next;
} node_t;

typedef struct heap_s {
    int32_t    heapsize;
    node_t  ** array;
} heap_t;

heap_t  * hp_create        ( int32_t heapsize);
void      hp_destroy       ( heap_t ** heap);
int8_t    hp_insert_key    ( heap_t * heap, int32_t data);
void      hp_find_key      ( heap_t * heap, int32_t data);
int32_t   hp_calc_hash_key ( heap_t * heap, int32_t data);
#endif