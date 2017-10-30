#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <stdlib.h>

#define BUFMAX 21
#define DICMAX 20000

typedef struct data_s {
    char   word[BUFMAX];
    size_t word_size;
} data_t;

int32_t   main_compare (const void * const key1, const void * const key2);
void      main_destroy (void **data);
void      main_print   (const void * const data);

#endif