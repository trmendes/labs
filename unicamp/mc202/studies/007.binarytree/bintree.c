#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bintree.h"

tree_t * tr_create() {
    tree_t * tree = calloc(1, sizeof(tree_t));
    return (tree_t *) tree;
}

int32_t tr_destroy(tree_t * t) {
    if (t == NULL)
	return ERR_TREE_NULL;
    if (t->root == NULL)
	return EMPTY_TREE;

    return SUCCESS;
}

int32_t tr_insert_by_value(tree_t * t, int32_t data) {
    if (t == NULL)
	return ERR_TREE_NULL;

    leaf_t * potencialSpace = NULL;
    leaf_t * leaf = calloc(1, sizeof(leaf_t));

    if (leaf == NULL)
	return ERR_MALLOC;

    leaf->data.id = data;

    if (t->root == NULL) {
	t->root = leaf;
    } else {
	potencialSpace = t->root;

	while (1) {
	    if (potencialSpace->data.id >= data) {
		if (potencialSpace->right == NULL) {
		    potencialSpace->right = leaf;
		    break;
		} else {
		    potencialSpace = potencialSpace->right;
		}
	    } else {
		if (potencialSpace->left == NULL) {
		    potencialSpace->left = leaf;
		    break;
		} else {
		    potencialSpace = potencialSpace->left;
		}
	    }
	}
    }

    t->len++;

    return SUCCESS;
}

void tr_print(leaf_t * root, printType_e pType) {
    if (root == NULL)
	return;

    if (pType == IN_ODER) {
	printf("%d ", root->data.id);
	tr_print(root->left , pType);
	tr_print(root->right, pType);
    }

}
