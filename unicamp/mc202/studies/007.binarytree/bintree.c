#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bintree.h"

leaf_t * tr_create() {
    leaf_t * root = NULL;
    return root;
}

int32_t tr_destroy(leaf_t * root) {
    if (root == NULL)
	return ERR_TREE_NULL;

    tr_destroy(root->left);
    tr_destroy(root->right);
    free(root);
    root = NULL;

    return SUCCESS;
}

int32_t tr_insert_by_value_rc(leaf_t **l, int32_t key) {
    if (*l == NULL) {
	leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));
	if (leaf == NULL)
	    return ERR_MALLOC;
	leaf->data.id = key;
	*l = leaf;
    } else if (key < (*l)->data.id) {
	tr_insert_by_value_rc(&(*l)->left, key);
    } else {
	tr_insert_by_value_rc(&(*l)->right, key);
    }

    return SUCCESS;
}

int32_t tr_insert_by_value(leaf_t ** l, int32_t key) {

    leaf_t * potencialSpace = NULL;
    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));

    if (leaf == NULL)
	return ERR_MALLOC;

    leaf->data.id = key;

    if (*l == NULL) {
	*l = leaf;
    } else {
	potencialSpace = *l;

	while (1) {
	    if (key < potencialSpace->data.id) {
		if (potencialSpace->left == NULL) {
		    potencialSpace->left = leaf;
		    break;
		} else {
		    potencialSpace = potencialSpace->left;
		}
	    } else {
		if (potencialSpace->right == NULL) {
		    potencialSpace->right= leaf;
		    break;
		} else {
		    potencialSpace = potencialSpace->right;
		}
	    }
	}
    }

    leaf->parent = potencialSpace;

    return SUCCESS;
}

leaf_t * tr_find_leaf_rc(leaf_t *l, int32_t key) {
    if (l == NULL)
	return (leaf_t *) NULL;
    if (l->data.id == key)
	return l;
    else if (key > l->data.id) {
	return tr_find_leaf(l->right, key);
    } else {
	return tr_find_leaf(l->left, key);
    }
}

leaf_t * tr_find_leaf(leaf_t *l, int32_t key) {
    while (l != NULL && l->data.id != key) {
	if (key < l->data.id) {
	    l = l->left;
	}
	else {
	    l = l->right;
	}
    }
    return l;
}

leaf_t * tr_find_min(leaf_t *l) {
    if (l == NULL)
	return (leaf_t *) NULL;
    while (l->left != NULL)
	l = l->left;
    return l;
}

leaf_t * tr_find_min_rc(leaf_t *l) {
    if (l == NULL)
	return (leaf_t *) NULL;
    if (l->left == NULL)
	return l;

    return tr_find_min(l->left);
}

leaf_t * tr_find_max(leaf_t *l) {
    if (l == NULL)
	return (leaf_t *) NULL;

    while (l->right != NULL)
	l = l->right;

    return l;
}

leaf_t * tr_find_max_rc(leaf_t *l) {
    if (l == NULL)
	return (leaf_t *) NULL;
    if (l->right == NULL)
	return l;

    return tr_find_max(l->right);
}

leaf_t * tr_find_pre(leaf_t * l) {
    if (l == NULL)
	return (leaf_t *) NULL;

    leaf_t * parent = NULL;

    if (l->left != NULL)
	return tr_find_max(l->left);
    else {
	parent = l->parent;
	while (parent != NULL && parent->left == l) {
	    l = parent;
	    parent = l->parent;
	}
    }
    return parent;
}

leaf_t * tr_find_suc(leaf_t *l) {
    if (l == NULL)
	return (leaf_t *) NULL;

    leaf_t * parent = NULL;

    if (l->right != NULL)
	return tr_find_min(l->right);
    else {
	parent = l->parent;
	while (parent != NULL && parent->right == l) {
	    l = parent;
	    parent = l->parent;
	}
    }

    return parent;
}

int32_t tr_delete(leaf_t *l) {

}

void tr_print(leaf_t * root, printType_e pType) {
    if (root == NULL)
	return;

    if (pType == PRE_ORDER) {
	printf("%d ", root->data.id);
	tr_print(root->left , pType);
	tr_print(root->right, pType);
    } else if (pType == IN_ORDER) {
	tr_print(root->left , pType);
	printf("%d ", root->data.id);
	tr_print(root->right, pType);
    } else if (pType == POS_ORDER) {
	tr_print(root->left , pType);
	tr_print(root->right, pType);
	printf("%d ", root->data.id);
    }
}
