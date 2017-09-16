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

    /*             /-------------200---------------\
     *      /------150------\             /------250------\
     *  /---130---\     /-150-\         /-230---\     /-260-\
     *  110     140     N     N         N     240     N     N
     *
     */

    leaf_t * root = tr_create();

    tr_insert_by_value(&root, 200);
    tr_insert_by_value(&root, 150);
    tr_insert_by_value(&root, 130);
    tr_insert_by_value(&root, 160);
    tr_insert_by_value(&root, 110);
    tr_insert_by_value(&root, 140);
    tr_insert_by_value(&root, 250);
    tr_insert_by_value(&root, 230);
    tr_insert_by_value(&root, 260);
    tr_insert_by_value(&root, 240);

    printf("Pre Order <root><left><right>\n");
    tr_print(root, PRE_ORDER);
    printf("\nIn Order  <left><root><right>\n");
    tr_print(root, IN_ORDER);
    printf("\nPos Order <left><right><root>\n");
    tr_print(root, POS_ORDER);
    printf("\n\n");

    min = tr_find_min(root);
    max = tr_find_max(root);
    printf("Min: %d\n", min->data.id);
    printf("Max: %d\n", max->data.id);
    printf("\n");

    leaf = tr_find_leaf(root, 1);
    suc = tr_find_suc(leaf);
    printf("Suc of %d is %d\n", leaf->data.id, suc->data.id);

    leaf = tr_find_leaf(root, 5);
    pre = tr_find_pre(leaf);
    printf("Pre of %d is %d\n", leaf->data.id, pre->data.id);

    return EXIT_SUCCESS;
}
