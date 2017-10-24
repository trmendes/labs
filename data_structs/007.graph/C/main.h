#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>

typedef struct data_s {
    int32_t key;
} data_t;

int32_t   compare (const void * const key1, const void * const key2);
void      destroy (void **data);
void      print   (const void * const data);

#endif