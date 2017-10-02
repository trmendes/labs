#include <stdint.h>
#include <stdlib.h>
#include "heap.h"

int32_t main() {
    heap_ctrl_t * h = hp_create(11);
    hp_insert_max(h, 88);
    hp_insert_max(h, 85);
    hp_insert_max(h, 83);
    hp_insert_max(h, 72);
    hp_insert_max(h, 73);
    hp_insert_max(h, 42);
    hp_insert_max(h, 57);
    hp_insert_max(h, 6);
    hp_insert_max(h, 48);
    hp_insert_max(h, 60);
    hp_print(h);
    hp_sort(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    hp_remove_max(h);
    hp_print(h);
    return EXIT_SUCCESS;
}
