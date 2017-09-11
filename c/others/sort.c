#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int reverse(const void *a, const void *b);
int order(const void *a, const void *b);

int reverse(const void *a, const void *b) {
    int32_t x = *((int32_t *)a);
    int32_t y = *((int32_t *)b);
    return y-x;
}

int order(const void *a, const void *b) {
    int32_t x = *((int32_t *)a);
    int32_t y = *((int32_t *)b);
    return x-y;
}

int32_t main(int32_t argc, char ** argv) {
    int32_t array[] = { 6, 4, 2, 9, 20, 10 };
    int32_t i;
    qsort(array, 6, sizeof(int32_t), order);
    for (i = 0; i < 6; i++) {
	printf("%d ", array[i]);
    }
    printf("\n");
    qsort(array, 6, sizeof(int32_t), reverse);
    for (i = 0; i < 6; i++) {
	printf("%d ", array[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}