#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "stack.h"

stack_t * stack_init(void (*destroy) (void **), void (*print)(const void *)) {
    if (destroy == NULL) {
	errno = STK_FAIL_ARGS;
	return (stack_t *) NULL;
    }

    stack_t *stack = (stack_t *) calloc(1, sizeof(stack_t));

    if (stack == (stack_t *) NULL)
	return (stack_t *) NULL;

    stack->destroy = destroy;
    stack->print = print;

    errno = STK_SUCCESS;
    return stack;
}

void stack_destroy(stack_t **stack) {
    if (*stack == (stack_t *) NULL) {
	errno = STK_NULL;
	return;
    }

    stack_element_t *element = (stack_element_t *) (*stack)->top;
    stack_element_t *prev_element = (stack_element_t *) NULL;

    while (element != (stack_element_t *) NULL) {
	(*stack)->destroy((void **) &(element->data));
	prev_element = element;
	element = element->next;

	memset(prev_element, 0x00, sizeof(stack_element_t));
	free(prev_element);
	prev_element = (stack_element_t *) NULL;
    }
    memset(*stack, 0x00, sizeof(stack_t));
    free(*stack);
    *stack = (stack_t *) NULL;
    errno = STK_SUCCESS;
}

int8_t stack_push(stack_t *stack, const void *data) {
    if (stack == (stack_t *) NULL)
	return STK_NULL;

    stack_element_t * new_element = (stack_element_t *) calloc(1, sizeof(stack_element_t));

    if (new_element == (stack_element_t *) NULL)
	return STK_FAIL_MALLOC;

    new_element->data = (void *) data;

    if (stack->top != (stack_element_t *) NULL) {
	new_element->next = stack->top;
	stack->top = new_element;
    } else {
	stack->top = new_element;
    }

    ++stack->len;

    return STK_SUCCESS;
}

void * stack_pop(stack_t *stack) {
    if (stack == (stack_t *) NULL) {
	errno = STK_NULL;
	return (void *) NULL;
    }

    if (stack->len == 0) {
	errno = STK_EMPTY;
	return (void *) NULL;
    }

    if (stack->top == (stack_element_t *) NULL) {
	errno = STK_EMPTY;
	return (void *) NULL;
    }

    stack_element_t * new_top = stack->top->next;

    void * data = stack->top->data;
    memset(stack->top, 0x00, sizeof(stack_element_t));
    free(stack->top);
    stack->top = (stack_element_t *) NULL;
    --stack->len;
    stack->top = new_top;

    errno = STK_SUCCESS;
    return data;
}

void stack_print_elements(stack_t *stack) {
    if (stack == (stack_t *) NULL) {
	errno = STK_NULL;
	return;
    }
    if (stack->len == 0) {
	errno = STK_EMPTY;
	return;
    }

    if (stack->print == NULL) {
	errno = STK_FUNCTION_NULL;
	return;
    }

    stack_element_t * element = stack->top;

    if (stack->len > 0) {
	printf("[ ");
	while (element != (stack_element_t *) NULL) {
	    stack->print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = STK_SUCCESS;
}
