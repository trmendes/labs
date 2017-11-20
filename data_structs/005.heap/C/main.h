#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>

typedef struct data_s {
    int32_t key;
} data_t;

int32_t   update  (void * data_a, void * data_b);
int32_t   compare (void * key1, void * key2);
void      destroy (void **data);
void      print   (void * data);

#endif