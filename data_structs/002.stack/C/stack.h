#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <stdlib.h>

#define STK_FUNCTION_NULL    -5
#define STK_EMPTY            -4
#define STK_FAIL_MALLOC      -3
#define STK_NULL             -2
#define STK_FAIL_ARGS        -1
#define STK_SUCCESS           0

typedef struct stack_element_s {
    void                   *data;
    struct stack_element_s *next;
} stack_element_t;

typedef struct stack_s {
    size_t           len;
    void             (*destroy) (void **data);
    void             (*print)   (const void *data);
    stack_element_t   *top;
} stack_t;

stack_t * stack_init            (void (*destroy)(void **), void (*print)(const void *));
void      stack_destroy         (stack_t **stack);
void    * stack_pop             (stack_t *stack);
int8_t    stack_push            (stack_t *stack, const void *data);
void      stack_print_elements  (stack_t *stack);

#endif