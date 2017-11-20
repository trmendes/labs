#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <stdlib.h>

#define STK_FUNCTION_NULL    (-5)
#define STK_EMPTY            (-4)
#define STK_FAIL_MALLOC      (-3)
#define STK_NULL             (-2)
#define STK_FAIL_ARGS        (-1)
#define STK_SUCCESS          (0)

typedef void (*destroy_ft) (void **data);
typedef void (*print_ft)   (void * data);

typedef struct stack_element_s {
    void                   *data;
    struct stack_element_s *next;
} stack_element_t;

typedef struct stack_api_s {
    print_ft         print;
} stack_api_t;

typedef struct stack_s {
    size_t           len;
    stack_api_t      api;
    stack_element_t *top;
} stack_t;

stack_t * stack_init            (print_ft print);
void      stack_destroy         (stack_t **stack, destroy_ft destroy);
void    * stack_pop             (stack_t *stack);
int8_t    stack_push            (stack_t *stack, void *data);
void      stack_print_elements  (stack_t *stack);

#endif