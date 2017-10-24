#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "queue.h"

int32_t main() {
    queue_t * queue = queue_init(destroy, print);

    data_t * data = NULL;

    data = calloc(1, sizeof(*data));
    data->key = 1;
    queue_add(queue, data);

    data = calloc(1, sizeof(*data));
    data->key = 2;
    queue_add(queue, data);

    data = calloc(1, sizeof(*data));
    data->key = 3;
    queue_add(queue, data);

    data = calloc(1, sizeof(*data));
    data->key = 4;
    queue_add(queue, data);

    data = calloc(1, sizeof(*data));
    data->key = 5;
    queue_add(queue, data);

    queue_print_elements(queue);

    data = (data_t *) queue_get(queue);
    printf("Queue GET %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    data = (data_t *) queue_get(queue);
    printf("Queue GET %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    data = (data_t *) queue_get(queue);
    printf("Queue GET %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);

    queue_destroy(&queue);

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

