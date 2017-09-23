#include "bintree.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int32_t main() {
    leaf_t * root = tr_create();

    tr_insert_by_value(&root, 50);
    tr_insert_by_value(&root, 40);
    tr_insert_by_value(&root, 45);

    tr_print(root, PRE_ORDER);

    printf("\n");
    return EXIT_SUCCESS;
}
