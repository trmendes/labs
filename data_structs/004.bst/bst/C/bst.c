#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "bst.h"

/* Private prototypes */

void         bst_destroy_leaf      (bst_leaf_t * leaf, bst_tree_t * tree);
void         bst_remove_swap       (bst_leaf_t **r, bst_leaf_t * u, bst_leaf_t * v);
void       * bst_find_data_leaf    (bst_tree_t * tree, void *data);
bst_leaf_t * bst_find_max_leaf     (bst_leaf_t * leaf);
bst_leaf_t * bst_find_min_leaf     (bst_leaf_t * leaf);
bst_leaf_t * bst_find_pre_leaf     (bst_tree_t * tree, void *data);
bst_leaf_t * bst_find_suc_leaf     (bst_tree_t * tree, void *data);
void         bst_print_tree_leaf   (bst_leaf_t * leaf, const bst_transversal_e type, bst_tree_t const * tree);

bst_tree_t * bst_init(compare_ft compare, destroy_ft destroy, print_ft print) {
    if (compare == NULL) {
	errno = BST_FAIL_ARGS;
	return NULL;
    }

    if (destroy == NULL) {
	errno = BST_FAIL_ARGS;
	return NULL;
    }

    bst_tree_t * tree = calloc(1, sizeof(*tree));

    if (tree == NULL) {
	errno = BST_FAIL_MALLOC;
	return NULL;
    }

    tree->compare = compare;
    tree->destroy = destroy;
    tree->print = print;

    errno = BST_SUCCESS;
    return tree;
}

void bst_destroy_leaf(bst_leaf_t * leaf, bst_tree_t * tree) {
    if (leaf == NULL)
	return;

    bst_destroy_leaf(leaf->left, tree);
    bst_destroy_leaf(leaf->right, tree);

    tree->destroy(&leaf->data);
    memset(leaf, 0x00, sizeof(*leaf));
    free(leaf);
}

void bst_destroy(bst_tree_t **tree) {
    if (*tree == NULL) {
	errno = BST_NULL;
	return;
    }

    bst_destroy_leaf((*tree)->root, *tree);

    memset((*tree), 0x00, sizeof(**tree));
    free(*tree);
    *tree = NULL;

    errno = BST_SUCCESS;
}

int8_t bst_insert(bst_tree_t *tree, void *data) {
    if (tree == NULL)
	return BST_NULL;

    if (data == NULL)
	return BST_FAIL_ARGS;

    bst_leaf_t * potential_parent = NULL;
    bst_leaf_t * new_leaf = NULL;

    new_leaf = calloc(1, sizeof(*new_leaf));

    if (new_leaf == NULL) {
	return BST_FAIL_MALLOC;
    }

    new_leaf->data = data;

    if (tree->root == NULL) {
	new_leaf->parent = NULL;
	tree->root = new_leaf;
    } else {
	potential_parent = tree->root;
	while (1) {
	    if (tree->compare(data, potential_parent->data) >= 0) {
		if (potential_parent->right == NULL) {
		    new_leaf->parent = potential_parent;
		    potential_parent->right = new_leaf;
		    break;
		} else {
		    potential_parent = potential_parent->right;
		}
	    } else {
		if (potential_parent->left == NULL) {
		    new_leaf->parent = potential_parent;
		    potential_parent->left = new_leaf;
		    break;
		} else {
		    potential_parent = potential_parent->left;
		}
	    }
	}
    }

    return BST_SUCCESS;
}


void bst_remove_swap(bst_leaf_t **r, bst_leaf_t * u, bst_leaf_t * v) {
    if (u->parent == NULL) {
	*r = v;
    }
    else if (u == u->parent->left) {
	u->parent->left = v;
    }
    else {
	u->parent->right = v;
    }

    if (v != NULL) {
	v->parent = u->parent;
    }
}

int8_t bst_remove(bst_tree_t *tree, void *data) {
    if (tree == NULL)
	return BST_NULL;

    if (data == NULL)
	return BST_FAIL_ARGS;

    bst_leaf_t * leaf_to_remove = bst_find_data_leaf(tree, data);
    bst_leaf_t * r_leaf_min = NULL;
    void * tmp = NULL;

    if (leaf_to_remove == NULL)
	return BST_DATA_NOT_FOUND;

    if (leaf_to_remove->left == NULL) {
	bst_remove_swap(&(tree->root), leaf_to_remove, leaf_to_remove->right);
    } else if (leaf_to_remove->right == NULL) {
	bst_remove_swap(&(tree->root), leaf_to_remove, leaf_to_remove->left);
    } else {
	r_leaf_min = bst_find_min_leaf(leaf_to_remove->right);
	/* Get the data from the minimum to make a copy of it */
	tmp = leaf_to_remove->data;
	/* Copy the min data to the place where we want to delete the node */
	leaf_to_remove->data = r_leaf_min->data;
	/* Send the data we want to delte to the node we made a copy */
	r_leaf_min->data = tmp;
	/* Now we are gonna delete an easy node to delete */
	leaf_to_remove = r_leaf_min;
	/* As we are working with minimum we know it came from the left
	 * side of a parent */
	r_leaf_min->parent->left = NULL;
    }

    tree->destroy(&(leaf_to_remove->data));
    memset(leaf_to_remove, 0x00, sizeof(*leaf_to_remove));
    free(leaf_to_remove);

    return BST_SUCCESS;
}

void * bst_find_data(bst_tree_t *tree, void *data) {
    bst_leaf_t * leaf = bst_find_data_leaf(tree, data);

    if (leaf == NULL)
	return NULL;

    return leaf->data;
}

void * bst_find_data_leaf(bst_tree_t *tree, void *data) {
    if (tree == NULL) {
	errno = BST_NULL;
	return NULL;
    }

    if (data == NULL) {
	errno = BST_FAIL_ARGS;
	return NULL;
    }

    bst_leaf_t * the_leaf = tree->root;

    while ((the_leaf != NULL) && (tree->compare(data, the_leaf->data) != 0)) {
	if (tree->compare(data, the_leaf->data) > 0)
	    the_leaf = the_leaf->right;
	else
	    the_leaf = the_leaf->left;
    }

    if (the_leaf == NULL) {
	errno = BST_DATA_NOT_FOUND;
	return NULL;
    }

    errno = BST_SUCCESS;
    return the_leaf;
}

void * bst_find_max(bst_tree_t * tree) {
    bst_leaf_t * leaf = bst_find_max_leaf(tree->root);

    if (leaf == NULL)
	return NULL;

    return leaf->data;
}

bst_leaf_t * bst_find_max_leaf(bst_leaf_t * leaf) {
    if (leaf == NULL) {
	errno = BST_NULL;
	return NULL;
    }

    bst_leaf_t * max_leaf = leaf;

    while (max_leaf->right != NULL) {
	max_leaf = max_leaf->right;
    }

    return max_leaf;
}

void * bst_find_min(bst_tree_t *tree) {
    bst_leaf_t * leaf = bst_find_min_leaf(tree->root);

    if (leaf == NULL)
	return NULL;

    return leaf->data;
}

bst_leaf_t * bst_find_min_leaf(bst_leaf_t *leaf) {
    if (leaf == NULL) {
	errno = BST_NULL;
	return NULL;
    }

    bst_leaf_t * min_leaf = leaf;

    while (min_leaf->left != NULL) {
	min_leaf = min_leaf->left;
    }

    return min_leaf;
}

void * bst_find_pre(bst_tree_t *tree, void * data) {
    bst_leaf_t * leaf = bst_find_pre_leaf(tree, data);

    if (leaf == NULL)
	return NULL;

    return leaf->data;
}

bst_leaf_t * bst_find_pre_leaf(bst_tree_t *tree, void * data) {
    bst_leaf_t * leaf = bst_find_data_leaf(tree, data);

    if (leaf == NULL)
	return NULL;

    bst_leaf_t * potential_pre = leaf->parent;

    if (leaf->left != NULL) {
	potential_pre = bst_find_max_leaf(leaf->left);
    } else {
	while ((potential_pre != NULL) && (potential_pre->left == leaf)) {
	    leaf = potential_pre;
	    potential_pre = leaf->parent;
	}
    }

    return potential_pre;
}

void * bst_find_suc(bst_tree_t *tree, void *data) {
    bst_leaf_t * leaf = bst_find_suc_leaf(tree, data);

    if (leaf == NULL)
	return NULL;

    return leaf->data;
}

bst_leaf_t * bst_find_suc_leaf(bst_tree_t *tree, void *data) {
    bst_leaf_t * leaf = bst_find_data_leaf(tree, data);

    if (leaf == NULL)
	return NULL;

    bst_leaf_t * potential_suc = leaf->parent;

    if (leaf->right != NULL) {
	potential_suc = bst_find_min_leaf(leaf->right);
    } else {
	while ((potential_suc != NULL) && (potential_suc->right == leaf)) {
	    leaf = potential_suc;
	    potential_suc = leaf->parent;
	}
    }

    return potential_suc;
}

void bst_print_tree(bst_tree_t const * const tree, const bst_transversal_e type) {
    if (tree == NULL) {
	errno = BST_NULL;
	return;
    }

    bst_print_tree_leaf(tree->root, type, tree);

    printf("\n");

    errno = BST_SUCCESS;
}

void bst_print_tree_leaf(bst_leaf_t * leaf, const bst_transversal_e type, bst_tree_t const * tree) {
    if (leaf == NULL)
	return;

    switch (type) {
	case PRE_ORDER:
	    tree->print(leaf->data);
	    bst_print_tree_leaf(leaf->left, type, tree);
	    bst_print_tree_leaf(leaf->right, type, tree);
	    break;
	case IN_ORDER:
	    bst_print_tree_leaf(leaf->left, type, tree);
	    tree->print(leaf->data);
	    bst_print_tree_leaf(leaf->right, type, tree);
	    break;
	case POS_ORDER:
	    bst_print_tree_leaf(leaf->left, type, tree);
	    bst_print_tree_leaf(leaf->right, type, tree);
	    tree->print(leaf->data);
	    break;
    }
}
