#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "heap.h"

int32_t main() {
    heap_t * heap = hp_init(17, compare, print);
    data_t * data = NULL;

    data = calloc(1, sizeof(*data));
    data->key = 54;
    hp_insert(heap, data);

    data = calloc(1, sizeof(*data));
    data->key = 55;
    hp_insert(heap, data);

    data = calloc(1, sizeof(*data));
    data->key = 56;
    hp_insert(heap, data);

    data = calloc(1, sizeof(*data));
    data->key = 30;
    hp_insert(heap, data);

    data = calloc(1, sizeof(*data));
    data->key = 20;
    hp_insert(heap, data);

    data = calloc(1, sizeof(*data));
    data->key = 100;
    hp_insert(heap, data);

    hp_print(heap);

    data = hp_get(heap);
    printf("Removed: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);
    hp_print(heap);

    data = hp_get(heap);
    printf("Removed: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);
    hp_print(heap);

    data = hp_get(heap);
    printf("Removed: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);
    hp_print(heap);

    data = hp_get(heap);
    printf("Removed: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);
    hp_print(heap);

    data = calloc(1, sizeof(*data));
    data->key = 10;
    hp_insert(heap, data);
    hp_print(heap);

    data = hp_get(heap);
    printf("Removed: %d\n", data->key);
    memset(data, 0x00, sizeof(*data));
    free(data);
    hp_print(heap);

    hp_destroy(heap, destroy);

    return EXIT_SUCCESS;
}

int32_t compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    //printf("Compare: %d %d: %d\n", a->key, b->key, (a->key - b->key));
    return a->key - b->key;
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

