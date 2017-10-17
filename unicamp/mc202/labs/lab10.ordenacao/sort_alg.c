#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "sort_alg.h"


void sort_glibqsort (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *)) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* CODE */
    /* ---------------------------------------------------------------------*/
    qsort(vector, len, block, compare);
    /* ---------------------------------------------------------------------*/
    /* END OF CODE */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("glib_qsort,%lu,%f\n", len, cpu_time_used);
}

void sort_bubble(void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *)) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* CODE */
    /* ---------------------------------------------------------------------*/
    if (vector == (void *) NULL) {
	errno = SORT_ERR_VECTOR_NULL;
	return;
    }

    char * prev = (char *) calloc(1, block);

    if (prev == (char *) NULL) {
	errno = SORT_ERR_MALLOC;
	return;
    }

    size_t i, j;
    char * array = (char *) vector;

    for (i = 1; i <= len - 1; ++i) {
	for (j = len -1; j >= i; --j) {
	    memcpy(prev,  &array[(j - 1) * block], block);
	    if (compare(prev, &array[j * block]) > 0) {
		memcpy(&array[(j - 1) * block], &array[j * block], block);
		memcpy(&array[j * block], prev, block);
	    }
	}
    }

    memset(prev, 0x00, block);
    free(prev);
    /* ---------------------------------------------------------------------*/
    /* END OF CODE */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("bubble_sort,%lu,%f\n", len, cpu_time_used);
}

void sort_selection(void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *)) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* CODE */
    /* ---------------------------------------------------------------------*/
    if (vector == (void *) NULL) {
	errno = SORT_ERR_VECTOR_NULL;
	return;
    }

    char * first = (char *) calloc(1, block);

    if (first == (char *) NULL) {
	errno = SORT_ERR_MALLOC;
	return;
    }

    size_t i, j, max;
    char * array = (char *) vector;

    for (i = len - 1; i > 0; --i) {
	max = 0;
	for (j = 1; j <= i; ++j) {
	    if (compare(&array[j * block], &array[max * block]) > 0) {
		max = j;
	    }
	}
	memcpy(first, &array[i * block], block);
	memcpy(&array[i * block], &array[max * block], block);
	memcpy(&array[max * block], first, block);
    }
    memset(first, 0x00, block);
    free(first);
    /* ---------------------------------------------------------------------*/
    /* END OF CODE */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("selection_sort,%lu,%f\n", len, cpu_time_used);
}


void sort_insertion(void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *)) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* CODE */
    /* ---------------------------------------------------------------------*/
    if (vector == (void *) NULL) {
	errno = SORT_ERR_VECTOR_NULL;
	return;
    }

    char * key = (char *) calloc(1, block);

    if (key == (char *) NULL) {
	errno = SORT_ERR_MALLOC;
	return;
    }

    size_t j;
    int32_t i;

    char * array = (char *) vector;

    for (j = 1; j < len ; ++j) {
	memcpy(key, &array[block * j], block);
	i = j - 1;
	while ((i >= 0) && (compare(&array[block * i], key) > 0)) {
	    memcpy(&array[(i + 1) * block], &array[i * block], block);
	    --i;
	}
	memcpy(&array[(i + 1) * block], key, block);
    }

    memset(key, 0x00, block);
    free(key);
    /* ---------------------------------------------------------------------*/
    /* END OF CODE */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("insertion_sort,%lu,%f\n", len, cpu_time_used);
}

void sort_shell(void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *)) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* CODE */
    /* ---------------------------------------------------------------------*/
    if (vector == (void *) NULL) {
	errno = SORT_ERR_VECTOR_NULL;
	return;
    }

    char * first = (char *) calloc(1, block);

    if (first == (char *) NULL) {
	errno = SORT_ERR_MALLOC;
	return;
    }

    size_t i;
    int32_t window = floor(len / 2);
    char * array = (char *) vector;

    while (window > 1) {
	for (i = 0; i < len - window ; i+=window) {
	    if (compare(&array[i * block], &array[(i + window) * block]) > 0) {
		memcpy(first, &array[i * block], block);
		memcpy(&array[i * block], &array[(i + window) * block], block);
		memcpy(&array[(i + window) * block], first, block);
	    }
	}
	window = floor(window / 2);
    }

    memset(first, 0x00, block);
    free(first);
    /* ---------------------------------------------------------------------*/
    /* END OF CODE */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("shell_sort,%lu,%f\n", len, cpu_time_used);
}
