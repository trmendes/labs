#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

stack_t * stack_init(print_ft print) {
    stack_t *stack = calloc(1, sizeof(*stack));

    if (stack == NULL)
        return NULL;

    stack->api.print = print;

    errno = STK_SUCCESS;
    return stack;
}

void stack_destroy(stack_t **stack, destroy_ft destroy) {
    if (*stack == NULL) {
        errno = STK_NULL;
        return;
    }

    stack_element_t *element = (*stack)->top;
    stack_element_t *prev_element = NULL;

    while (element != NULL) {
		if (destroy != NULL)
			destroy(&(element->data));
        prev_element = element;
        element = element->next;

        memset(prev_element, 0x00, sizeof(*prev_element));
        free(prev_element);
        prev_element = NULL;
    }
    memset(*stack, 0x00, sizeof(**stack));
    free(*stack);
    *stack = NULL;
    errno = STK_SUCCESS;
}

int8_t stack_push(stack_t *stack, void *data) {
    if (stack == NULL)
        return STK_NULL;

    stack_element_t * new_element = calloc(1, sizeof(*new_element));

    if (new_element == NULL)
        return STK_FAIL_MALLOC;

    new_element->data = data;

    if (stack->top != NULL) {
        new_element->next = stack->top;
        stack->top = new_element;
    } else {
        stack->top = new_element;
    }

    ++stack->len;

    return STK_SUCCESS;
}

void * stack_pop(stack_t *stack) {
    if (stack == NULL) {
        errno = STK_NULL;
        return NULL;
    }

    if (stack->len == 0) {
        errno = STK_EMPTY;
        return NULL;
    }

    if (stack->top == NULL) {
        errno = STK_EMPTY;
        return NULL;
    }

    stack_element_t * new_top = stack->top->next;

    void * data = stack->top->data;
    memset(stack->top, 0x00, sizeof(*(stack->top)));
    free(stack->top);
    stack->top = NULL;
    --stack->len;
    stack->top = new_top;

    errno = STK_SUCCESS;
    return data;
}

void stack_print_elements(stack_t *stack) {
    if (stack == NULL) {
        errno = STK_NULL;
        return;
    }
    if (stack->len == 0) {
        errno = STK_EMPTY;
        return;
    }

    if (stack->api.print == NULL) {
        errno = STK_FUNCTION_NULL;
        return;
    }

    stack_element_t * element = stack->top;

    if (stack->len > 0) {
        printf("[ ");
        while (element != NULL) {
            stack->api.print(element->data);
            element = element->next;
        }
        printf("]\n");
    }

    errno = STK_SUCCESS;
}
