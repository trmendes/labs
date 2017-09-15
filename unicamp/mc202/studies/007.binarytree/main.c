#include "bintree.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int32_t main() {
    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));
    leaf_t * min = NULL;
    leaf_t * max = NULL;
    leaf_t * suc = NULL;
    leaf_t * pre = NULL;

    leaf_t * root = tr_create();
    leaf_t * root2 = tr_create();

    tr_insert_by_value(&root, 4);
    tr_insert_by_value(&root, 2);
    tr_insert_by_value(&root, 3);
    tr_insert_by_value(&root, 1);
    tr_insert_by_value(&root, 5);
    tr_insert_by_value(&root, 6);
    tr_insert_by_value(&root, 300);


    tr_insert_by_value_rc(&root2, 4);
    tr_insert_by_value_rc(&root2, 2);
    tr_insert_by_value_rc(&root2, 3);
    tr_insert_by_value_rc(&root2, 1);
    tr_insert_by_value_rc(&root2, 5);
    tr_insert_by_value_rc(&root2, 6);
    tr_insert_by_value_rc(&root2, 400);

    tr_print(root, IN_ODER);
    printf("\n");
    tr_print(root2, IN_ODER);
    printf("\n");

    min = tr_find_min(root);
    max = tr_find_max(root);
    printf("Min: %d\n", min->data.id);
    printf("Max: %d\n", max->data.id);

    leaf = tr_find_leaf(root, 1);
    suc = tr_find_suc(leaf);
    printf("Suc of %d is %d\n", leaf->data.id, suc->data.id);

    leaf = tr_find_leaf(root, 5);
    pre = tr_find_pre(leaf);
    printf("Pre of %d is %d\n", leaf->data.id, pre->data.id);


    return EXIT_SUCCESS;
}
