#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bintree.h"
#include "queue.h"

leaf_t * tr_create() {
    leaf_t * root = (leaf_t *) NULL;
    return root;
}

int32_t tr_destroy(leaf_t * root) {
    if (root == (leaf_t *) NULL)
	return EMPTY_TREE;

    tr_destroy(root->left);
    tr_destroy(root->right);
    free(root);

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

    leaf_t * potencialSpace = (leaf_t *) NULL;
    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));

    if (leaf == (leaf_t *) NULL)
	return ERR_MALLOC;

    leaf->data.id = key;

    if (*l == (leaf_t *) NULL) {
	*l = leaf;
    } else {
	potencialSpace = *l;

	while (1) {
	    if (key < potencialSpace->data.id) {
		if (potencialSpace->left == (leaf_t *) NULL) {
		    potencialSpace->left = leaf;
		    leaf->parent = potencialSpace;
		    break;
		} else {
		    potencialSpace = potencialSpace->left;
		}
	    } else if (key > potencialSpace->data.id) {
		if (potencialSpace->right == (leaf_t *) NULL) {
		    potencialSpace->right= leaf;
		    leaf->parent = potencialSpace;
		    break;
		} else {
		    potencialSpace = potencialSpace->right;
		}
	    } else if (key == potencialSpace->data.id) {
		break;
	    }
	}
    }


    return SUCCESS;
}

leaf_t * tr_find_leaf_rc(leaf_t *l, int32_t key) {
    if (l == (leaf_t *) NULL)
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
    while (l != (leaf_t *) NULL && l->data.id != key) {
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
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;
    while (l->left != (leaf_t *) NULL)
	l = l->left;
    return l;
}

leaf_t * tr_find_min_rc(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;
    if (l->left == (leaf_t *) NULL)
	return l;

    return tr_find_min(l->left);
}

leaf_t * tr_find_max(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;

    while (l->right != (leaf_t *) NULL)
	l = l->right;

    return l;
}

leaf_t * tr_find_max_rc(leaf_t *l) {
    if (l == (leaf_t *) NULL)
	return (leaf_t *) NULL;
    if (l->right == (leaf_t *) NULL)
	return l;

    return tr_find_max(l->right);
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
    if (*r == NULL)
	return ERR_TREE_NULL;

    leaf_t * toremove = tr_find_leaf(*r, key);

    if (toremove == NULL)
	return ERR_NO_LEAF;

    if (toremove->left == NULL) {
	tr_replace(r, toremove, toremove->right);
    }
    else if (toremove->right == NULL) {
	tr_replace(r, toremove, toremove->left);
    }
    else {
	leaf_t * min = tr_find_min(toremove->right);
	if (min != NULL) {
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
    toremove = NULL;

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

    if (v != NULL) {
	v->parent = u->parent;
    }
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

void tr_print_breadth(leaf_t * root) {
    if (root == (leaf_t *) NULL)
	return;

    queue_t * q = qe_create();

    leaf_t * leaf = (leaf_t *) NULL;

    node_t * node = calloc(1, sizeof(node_t));
    node->leaf = root;

    qe_insert(q, node);

    while (qe_len(q) != 0) {
	leaf = (qe_get(q))->leaf;

	printf("%d ", leaf->data.id);

	if (leaf->left != NULL) {
	    node_t * nnode = calloc(1, sizeof(node_t));
	    nnode->leaf = leaf->left;
	    qe_insert(q, nnode);
	}

	if (leaf->right != NULL) {
	    node_t * nnode = calloc(1, sizeof(node_t));
	    nnode->leaf = leaf->right;
	    qe_insert(q, nnode);
	}

	leaf = (leaf_t *) NULL;
    }
}
