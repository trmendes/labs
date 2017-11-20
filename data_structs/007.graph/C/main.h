#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>

typedef struct data_s {
    char key;
} data_t;

int32_t   main_compare (void * key1, void * key2);
void      main_destroy (void **data);
void      main_print   (void * data);

#endif