#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int32_t main() {
    heap_t * heap = hp_create(10);
    hp_insert_key(heap, 10);
    hp_insert_key(heap, 29);
    hp_insert_key(heap, 1);
    hp_insert_key(heap, 23);
    hp_insert_key(heap, 120);
    hp_insert_key(heap, 34);
    hp_insert_key(heap, 13);
    hp_insert_key(heap, 11);
    hp_insert_key(heap, 1116);
    hp_insert_key(heap, 123);
    hp_insert_key(heap, 234);
    hp_find_key(heap, 10);
    hp_find_key(heap, 29);
    hp_find_key(heap, 0);
    hp_find_key(heap, 123);
    hp_destroy(&heap);
    return EXIT_SUCCESS;
}
