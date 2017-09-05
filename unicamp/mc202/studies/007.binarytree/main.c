#include "bintree.h"
#include <stdint.h>
#include <stdlib.h>

int32_t main(int32_t argc, char **argv) {
    tree_t * tree = tr_create();

    if (tree == NULL)
	return EXIT_FAILURE;

    tr_insert_by_value(tree, 4);
    tr_insert_by_value(tree, 2);
    tr_insert_by_value(tree, 3);
    tr_insert_by_value(tree, 1);
    tr_insert_by_value(tree, 5);
    tr_insert_by_value(tree, 6);

    tr_print(tree->root, IN_ODER);
    return EXIT_SUCCESS;
}
