#ifndef __HASH_H__
#define __HASH_H__

#include <stdint.h>
#include <stdlib.h>

#define ERR_NO_SPACE   -3
#define ERR_WRONG_DATA -2
#define ERR_HEAP_NULL  -1
#define SUCCESS         0

#define CHARMAX       250

typedef struct data_s {
    char    data[CHARMAX];
    int32_t idx;
} data_t;

typedef struct hash_s {
    int32_t          hashsize;
    int32_t          hashidx;
    data_t        ** array;
} hash_t;

hash_t      * hs_create        ( int32_t hashsize);
void          hs_destroy       ( hash_t ** hash);
int8_t        hs_insert_key    ( hash_t * hash, char * data);
void          hs_find_key      ( hash_t * hash, char * data);
int32_t       hs_remove_key    ( hash_t * hash, char * data);
unsigned long hs_hash_djb2     ( char *str);
int32_t       hs_hash1         ( unsigned long key, size_t size);
int32_t       hs_hash2         ( unsigned long key, size_t size);

#endif