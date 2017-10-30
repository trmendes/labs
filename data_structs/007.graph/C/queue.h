#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdint.h>
#include <stdlib.h>

#define QUEUE_FUNCTION_NULL    -5
#define QUEUE_EMPTY            -4
#define QUEUE_FAIL_MALLOC      -3
#define QUEUE_NULL             -2
#define QUEUE_ARGS_FAIL        -1
#define QUEUE_SUCCESS           0

typedef void (*destroy_ft) (void **data);
typedef void (*print_ft)   (const void * const data);

 typedef struct que_element_s {
    void                 *data;
    struct que_element_s *next;
} que_element_t;

typedef struct queue_s {
    size_t           len;
    que_element_t   *head;
    que_element_t   *tail;
} queue_t;

queue_t * queue_init           ();
void      queue_destroy        (queue_t **queue, destroy_ft destroy);
int8_t    queue_add            (queue_t *queue, const void *data);
void *    queue_get            (queue_t *queue);
void      queue_print_elements (queue_t *queue, print_ft print);

#endif