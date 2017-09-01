#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>

#define ERR_VECTOR_NULL  -1
#define ERR_VECTOR_EMPTY -2
#define SUCCESS           0

typedef struct cvector_s {
    int    * array;
    int      len;
    int      max;
    int      head;
} cvector_t;

cvector_t * cv_create       (int size);
int         cv_destroy      (cvector_t **a);
int         cv_insert       (cvector_t *a, int data);
int         cv_get          (cvector_t *a);
int         cv_len          (cvector_t *a);
void        cv_print        (cvector_t *a, char *msg);
void        cv_write_output (FILE *ofd, cvector_t *a, char *msg);

#endif
