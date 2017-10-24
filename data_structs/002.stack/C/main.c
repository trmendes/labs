#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "stack.h"

int32_t main() {
    stack_t * stack = stack_init(destroy, print);

    data_t * data = calloc(1, sizeof(*data));
    data->key = 0;
    stack_push(stack, data);

    data = calloc(1, sizeof(*data));
    data->key = 1;
    stack_push(stack, data);

    data = calloc(1, sizeof(*data));
    data->key = 2;
    stack_push(stack, data);

    data = calloc(1, sizeof(*data));
    data->key = 3;
    stack_push(stack, data);

    data = calloc(1, sizeof(*data));
    data->key = 4;
    stack_push(stack, data);

    stack_print_elements(stack);

    data = (data_t *) stack_pop(stack);
    printf("Pop: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    stack_print_elements(stack);

    data = (data_t *) stack_pop(stack);
    printf("Pop: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    stack_print_elements(stack);

    data = (data_t *) stack_pop(stack);
    printf("Pop: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    stack_print_elements(stack);

    stack_destroy(&stack);

    return EXIT_SUCCESS;
}

void destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}

