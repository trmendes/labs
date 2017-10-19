#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "sort.h"

#define ARRAY_SIZE 20
#define SEED 2000

int32_t main() {
    time_t t;
    srand((unsigned) time(&t));
    int32_t array[ARRAY_SIZE];
    int32_t array_to_sort[ARRAY_SIZE];

    size_t i;

    for (i = 0; i < ARRAY_SIZE; ++i) {
	array[i] = rand() % SEED;
    }

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_glibqsort((void *) array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_bubble(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_selection(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_insertion(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_shell(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //memcpy(array_to_sort, array, sizeof(array));
    //sort_quick(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    //TODO: FIX
    //memcpy(array_to_sort, array, sizeof(array));
    //sort_quick(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    //print(array_to_sort, ARRAY_SIZE);

    memcpy(array_to_sort, array, sizeof(array));
    sort_heap(array_to_sort, ARRAY_SIZE, sizeof(int32_t), compare);
    print(array_to_sort, ARRAY_SIZE);

return EXIT_SUCCESS;
}

int32_t compare(const void * key1, const void * key2) {
    int a = * (int *) key1;
    int b = * (int *) key2;
    return a - b;
}

void print(const int32_t *array, const size_t len) {
    for (size_t i = 0; i < len; ++i) {
	printf(" %d ", array[i]);
    }
    printf("\n");
}
