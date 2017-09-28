#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bintree.h"

#define LEAF      0
#define THREADED  1

leaf_t * tr_create() {
    leaf_t * root = (leaf_t *) NULL;
    return root;
}

int32_t tr_destroy(leaf_t * root) {
    if (root == (leaf_t *) NULL)
	return EMPTY_TREE;

    if (root->flags.left == LEAF)
	tr_destroy(root->left);
    if (root->flags.right == LEAF)
	tr_destroy(root->right);
    free(root);
    root = (leaf_t *) NULL;

    return SUCCESS;
}

int32_t tr_insert_by_value(leaf_t ** l, int32_t key) {

    leaf_t * potencialSpace = (leaf_t *) NULL;
    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));

    if (leaf == (leaf_t *) NULL)
	return ERR_MALLOC;

    leaf->data.id = key;

    if (*l == (leaf_t *) NULL) {
	*l = leaf;
	leaf->flags.left = THREADED;
	leaf->flags.right = THREADED;
    } else {
	potencialSpace = *l;

	while (1) {
	    if (key < potencialSpace->data.id) {
		if (potencialSpace->flags.left == THREADED) {

		    potencialSpace->left = leaf;
		    potencialSpace->flags.left = LEAF;

		    leaf->parent = potencialSpace;
		    leaf->left = tr_find_pre(leaf);
		    leaf->flags.left = THREADED;

		    leaf->right = tr_find_suc(leaf);
		    leaf->flags.right = THREADED;

		    printf("(L   ) %d\n", leaf->data.id);

		    if (leaf->right != NULL)
			printf("(L->R) %d\n", leaf->right->data.id);
		    if (leaf->left != NULL)
			printf("(L->L) %d\n", leaf->left->data.id);
		    break;
		} else {
		    if (potencialSpace->flags.left == LEAF)
			potencialSpace = potencialSpace->left;
		    else
			break;
		}
	    } else {
		if (potencialSpace->flags.right == THREADED) {

		    potencialSpace->right= leaf;
		    potencialSpace->flags.right = LEAF;

		    leaf->parent = potencialSpace;
		    leaf->left = tr_find_pre(leaf);
		    leaf->flags.left = THREADED;

		    leaf->right = tr_find_suc(leaf);
		    leaf->flags.right = THREADED;

		    printf("(R   ) %d\n", leaf->data.id);

		    if (leaf->right != NULL)
			printf("(L->R) %d\n", leaf->right->data.id);
		    if (leaf->left != NULL)
			printf("(L->L) %d\n", leaf->left->data.id);
		    break;
		} else {
		    if (potencialSpace->flags.right == LEAF)
			potencialSpace = potencialSpace->right;
		    else
			break;
		}
	    }
	}
    }

    return SUCCESS;
}

leaf_t * tr_find_leaf(leaf_t *l, int32_t key) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    if (l->data.id == key)
	return l;
    else if (key > l->data.id) {
	if (l->flags.right == LEAF)
	    return tr_find_leaf(l->right, key);
    } else {
	if (l->flags.left == LEAF)
	    return tr_find_leaf(l->left, key);
    }

    return (leaf_t *) NULL;
}

leaf_t * tr_find_min(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;
    while (l->left != (leaf_t *) NULL) {
	if (l->flags.left == LEAF)
	    l = l->left;
	else
	    break;
    }
    return l;
}

leaf_t * tr_find_max(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    while (l->right != (leaf_t *) NULL) {
	if (l->flags.right == LEAF)
	    l = l->right;
	else
	    break;
    }

    return l;
}

leaf_t * tr_find_pre(leaf_t * l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    leaf_t * parent = (leaf_t *) NULL;

    if (l->left != (leaf_t *) NULL)
	return tr_find_max(l->left);
    else {
	parent = l->parent;
	while (parent != (leaf_t *) NULL && parent->left == l) {
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
	while (parent != (leaf_t *) NULL && parent->right == l) {
	    l = parent;
	    parent = l->parent;
	}
    }

    return parent;
}

void tr_replace(leaf_t ** r, leaf_t *a, leaf_t *b);

int32_t tr_delete(leaf_t **r, int32_t key) {
    if (*r == (leaf_t *) NULL)
	return ERR_TREE_NULL;

    leaf_t * toremove = tr_find_leaf(*r, key);

    if (toremove == (leaf_t *) NULL)
	return ERR_NO_LEAF;

    if (toremove->left == (leaf_t *) NULL) {
	tr_replace(r, toremove, toremove->right);
    }
    else if (toremove->right == (leaf_t *) NULL) {
	tr_replace(r, toremove, toremove->left);
    }
    else {
	leaf_t * min = tr_find_min(toremove->right);
	if (min != (leaf_t *) NULL) {
	    if (min->parent != toremove) {
		tr_replace(r, min, min->right);
		min->right = toremove->right;
		min->right->parent = min;
	    }
	    tr_replace(r, toremove, min);
	    min->left = toremove->left;
	    min->left->parent = min;
	}
    }

    free(toremove);
    toremove = (leaf_t *) NULL;

    return SUCCESS;
}

void tr_replace(leaf_t **r, leaf_t * u, leaf_t * v) {
    if (u->parent == (leaf_t *) NULL) {
	*r = v;
    }
    else if (u == u->parent->left) {
	u->parent->left = v;
    }
    else {
	u->parent->right = v;
    }

    if (v != (leaf_t *) NULL) {
	v->parent = u->parent;
    }
}


void tr_print(leaf_t * root, printType_e pType) {
    if (root == (leaf_t *) NULL)
	return;

    if (pType == PRE_ORDER) {
	leaf_t * p = (leaf_t *) NULL;
	p = tr_find_min(root);
	if (p != (leaf_t *) NULL) {
	    while (p != (leaf_t *) NULL) {
		printf("%d ", p->data.id);
		if (p->parent == NULL)
		    p = tr_find_min(p->right);
		else
		    p = p->right;
	    }
	}
    } else if (pType == IN_ORDER) {
	printf("%d ", root->data.id);
	if (root->flags.left == LEAF)
	    tr_print(root->left , pType);
	if (root->flags.right == LEAF)
	    tr_print(root->right, pType);
    } else if (pType == POS_ORDER) {
	if (root->flags.left == LEAF)
	    tr_print(root->left , pType);
	if (root->flags.right == LEAF)
	    tr_print(root->right, pType);
	printf("%d ", root->data.id);
    }
}
