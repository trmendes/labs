#ifndef __SORT_ALG_H__
#define __SORT_ALG_H__

#include <stdint.h>
#include <stdlib.h>

#define SORT_ERR_MALLOC      -2
#define SORT_ERR_VECTOR_NULL -1
#define SORT_SUCCESS          0

void sort_glibqsort  (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_bubble     (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_selection  (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_insertion  (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_shell      (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));

void sort_quick      (void *vector, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_merge_sort (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_bucket     (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_counting   (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));
void sort_radix      (void *vector, const size_t len, const size_t block, int32_t (*compare)(const void *, const void *));

#endif