#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bintree.h"

leaf_t * tr_create() {
    return (leaf_t *) NULL;
}

void tr_destroy(leaf_t * root) {
    if (root == (leaf_t *) NULL)
	return;

    tr_destroy(root->left);
    tr_destroy(root->right);

    free(root);
    root = (leaf_t *) NULL;
}

int32_t tr_insert_by_value(leaf_t **l, int32_t key) {
    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));
    leaf_t * p = *l;

    if (leaf == (leaf_t *) NULL)
	return ERR_MALLOC;

    leaf->data.id = key;

    if (*l == NULL) {
	*l = leaf;
    } else {
	while (p != NULL) {
	    if (key > p->data.id) {
		if (p->left == (leaf_t *) NULL) {
		    p->left = leaf;
		    leaf->parent = p;
		    break;
		} else {
		    p = p->left;
		}
	    } else if (key < p->data.id) {
		if (p->right == (leaf_t *) NULL) {
		    p->right = leaf;
		    leaf->parent = p;
		    break;
		} else {
		    p = p->right;
		}
	    } else {
		break;
	    }
	}

	while (p->parent != (leaf_t *) NULL) {
	    if (p->parent->left == p) {
		--p->parent->avl_factor;
	    } else if (p->parent->right == p) {
		++p->parent->avl_factor;
	    }
	    p = p->parent;

	    if (p->avl_factor == AVL_MAX_LEFT) {
		tr_avl_rotete_left(&p);
	    }
	    if (p->avl_factor == AVL_MAX_RIGHT) {
		tr_avl_rotete_right(&p);
	    }
	}
    }

    return SUCCESS;
}

int32_t tr_avl_rotete_left(leaf_t ** root) {
    printf("--> Rotate Left %d\n", (*root)->data.id);
    return SUCCESS;
}
int32_t tr_avl_rotete_right(leaf_t ** root) {
    printf("--> Rotate Right %d\n", (*root)->data.id);
    return SUCCESS;
}

leaf_t * tr_find_leaf(leaf_t *l , int32_t key) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    while (l != (leaf_t *) NULL) {
	if (key < l->data.id)
	    l = l->left;
	else if (key > l->data.id)
	    l = l->right;
	else
	    break;
    }

    return l;
}

leaf_t * tr_find_min(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    while (l->left != (leaf_t *) NULL)
	l = l->left;

    return l;
}

leaf_t * tr_find_max(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    while (l->right != (leaf_t *) NULL)
	l = l->right;

    return l;
}

leaf_t * tr_find_pre(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    leaf_t *parent = (leaf_t *) NULL;

    if (l->left != (leaf_t *) NULL)
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
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    leaf_t * parent = (leaf_t *) NULL;

    if (l->right != (leaf_t *) NULL)
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

int32_t tr_delete(leaf_t **l, int32_t key) {
    return SUCCESS;
}

void tr_print(leaf_t * root, printType_e pType) {
    if (root == (leaf_t *) NULL)
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
