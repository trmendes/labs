#ifndef __DVECTOR_H__
#define __DVECTOR_H__

#include <stdint.h>

#define ERR_NO_VECTOR   -1
#define ERR_NO_ARRAY    -2
#define ERR_CANT_EXPAND -3
#define EMPTY_ARRAY     -4
#define NO_HEAD         -5
#define NO_TAIL         -6

#define SUCCESS          0

typedef struct sdvector {
    int32_t  orsize;
    int32_t  size;
    int32_t  len;
    uint8_t  alloc_cnt;
    int32_t  head_idx;
    int32_t *array;
} dvector;

dvector * dv_create             (int32_t size);
int8_t    dv_realloc            (dvector *v);
void      dv_destroy            (dvector *v);

int8_t    dv_insert_head        (dvector *v, int32_t value);
int8_t    dv_insert_tail        (dvector *v, int32_t value);

int8_t    dv_remove_tail        (dvector *v);
int8_t    dv_remove_head        (dvector *v);

void      dv_print_array_info   (dvector *v);
void      dv_print              (dvector *v, char *head);

#endif
