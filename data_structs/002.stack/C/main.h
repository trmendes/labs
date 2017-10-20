#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>

typedef struct data_s {
    int32_t key;
} data_t;

void      destroy (void **data);
void      print   (const void *data);

#endif