#ifndef __BST_PRIV_H__
#define __BST_PRIV_H__

#include "bst.h"

void         bst_destroy_leaf      (bst_leaf_t * leaf, bst_tree_t * tree);
void         bst_remove_swap       (bst_leaf_t **r, bst_leaf_t * u, bst_leaf_t * v);
void       * bst_find_data_leaf    (bst_tree_t * tree, void *data);
bst_leaf_t * bst_find_max_leaf     (bst_leaf_t * leaf);
bst_leaf_t * bst_find_min_leaf     (bst_leaf_t * leaf);
bst_leaf_t * bst_find_pre_leaf     (bst_tree_t * tree, void *data);
bst_leaf_t * bst_find_suc_leaf     (bst_tree_t * tree, void *data);
void         bst_print_tree_leaf   (bst_leaf_t * leaf, const bst_transversal_e type, bst_tree_t const * tree);


#endif
