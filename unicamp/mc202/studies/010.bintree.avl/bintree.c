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
	    if (key < p->data.id) {
		if (p->left == (leaf_t *) NULL) {
		    p->left = leaf;
		    leaf->parent = p;
		    break;
		} else {
		    p = p->left;
		}
	    } else if (key > p->data.id) {
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
#ifdef AVL
	p = leaf;

	/* AVL */
	while (p->parent != (leaf_t *) NULL) {

	    if (p->parent->left == p) {
		--p->parent->avl_factor;
	    } else if (p->parent->right == p) {
		++p->parent->avl_factor;
	    }

	    printf("-----> Fator de %d: %d\n", p->parent->data.id, p->parent->avl_factor);

	    if (p->parent->avl_factor == AVL_MIN) {
		if (p->avl_factor == 1) {
		    tr_avl_rotate_left(l, p);
		    p = p->parent;
		} 
		tr_avl_rotate_right(l, p->parent);
	    } else if (p->parent->avl_factor == AVL_MAX) {
		if (p->avl_factor == -1) {
		    tr_avl_rotate_right(l, p);
		    p = p->parent;
		}
		tr_avl_rotate_left(l, p->parent);
	    }

	    if (p->parent != NULL) {
		p = p->parent;
	    }
	}
#endif
    }

    return SUCCESS;
}

#ifdef AVL
int32_t tr_avl_rotate_right(leaf_t ** root, leaf_t * oldr) {
    if (oldr == NULL)
	return ERR_TREE_NULL;
    printf("\n---------------------------------\n");
    tr_print(*root, PRE_ORDER);

    leaf_t * pivot = oldr->left;

    printf("\n(R) Balanceado em: %d <-> %d\n", oldr->data.id, pivot->data.id);

    if (oldr->parent == (leaf_t *) NULL)
	*root = pivot;
    else {
	if (oldr->parent->left == oldr)
	    oldr->parent->left = pivot;
	else
	    oldr->parent->right = pivot;
    }

    oldr->left = pivot->right;
    pivot->right = oldr;

    pivot->parent = oldr->parent;
    oldr->parent = pivot;

    pivot->avl_factor = 0;
    oldr->avl_factor = 0;

    tr_print(*root, PRE_ORDER);

    printf("\n---------------------------------\n");
    return SUCCESS;
}

int32_t tr_avl_rotate_left(leaf_t ** root, leaf_t * oldr) {
    if (oldr == NULL)
	return ERR_TREE_NULL;
    printf("\n---------------------------------\n");
    tr_print(*root, PRE_ORDER);

    leaf_t * pivot = oldr->right;

    printf("\n(L) Balanceado em: %d <-> %d\n", oldr->data.id, pivot->data.id);

    if (oldr->parent == (leaf_t *) NULL)
	*root = pivot;
    else {
	if (oldr->parent->left == oldr)
	    oldr->parent->left = pivot;
	else
	    oldr->parent->right = pivot;
    }

    oldr->right = pivot->left;
    pivot->left = oldr;

    pivot->parent = oldr->parent;
    oldr->parent = pivot;

    pivot->avl_factor = 0;
    oldr->avl_factor = 0;

    tr_print(*root, PRE_ORDER);
    printf("\n---------------------------------\n");

    return SUCCESS;
}
#endif

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

void tr_replace(leaf_t ** root, leaf_t * old, leaf_t * new);

int32_t tr_delete(leaf_t **l, int32_t key) {
    if (*l == (leaf_t *) NULL)
	return ERR_TREE_NULL;

    leaf_t * p = tr_find_leaf(*l, key);
    leaf_t * replacement = (leaf_t *) NULL;

    if (p == (leaf_t *) NULL)
	return ERR_NO_LEAF;

    if (p->left == (leaf_t *) NULL) {
	tr_replace(l, p, p->right);
    } else if (p->right == (leaf_t *) NULL) {
	tr_replace(l, p, p->left);
    } else {
	replacement = tr_find_min(p->right);

	if (replacement != (leaf_t *) NULL) {
	    if (replacement->parent != p) {
		tr_replace(l, replacement, replacement->right);
		replacement->right = p->right;
		replacement->right->parent = replacement;
	    }
	    tr_replace(l, p, replacement);
	    replacement->left = p->left;
	    replacement->left->parent = replacement;
	}

    }

    free(p);
    p = NULL;

    return SUCCESS;
}

void tr_replace(leaf_t ** root, leaf_t * old, leaf_t * new) {
    if (old->parent == (leaf_t *) NULL)
	*root = new;
    else if (old == old->parent->left)
	old->parent->left = new;
    else
	old->parent->right = new;

    if (new != (leaf_t *) NULL)
	new->parent = old->parent;
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
