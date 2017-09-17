#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "bintree.h"

void tr_destroy(leaf_t *root) {
    if (root == NULL)
	return;
    tr_destroy(root->left);
    tr_destroy(root->right);
    free(root);
    root = NULL;
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

void tr_print_pre(leaf_t * root) {
    if (root == NULL)
	return;
    printf("%c", root->data.c);
    tr_print_pre(root->left);
    tr_print_pre(root->right);
}

void tr_print_in(leaf_t * root) {
    if (root == NULL)
	return;

    tr_print_in(root->left);
    printf("%c", root->data.c);
    tr_print_in(root->right);
}

void tr_print_pos(leaf_t * root) {
    if (root == NULL)
	return;

    tr_print_pos(root->left);
    tr_print_pos(root->right);
    printf("%c", root->data.c);
}

leaf_t * tr_create_leaf(char c) {

    leaf_t * leaf = (leaf_t *) calloc(1, sizeof(leaf_t));

    if (leaf == NULL)
	return NULL;

    int32_t key = toascii(c);

    leaf->data.id = key;
    leaf->data.c = c;

    return leaf;
}

leaf_t * tr_rebuild_tree(char * pre_order_str, char * in_order_str, size_t start, size_t end, size_t * preIdx) {
    if (pre_order_str == NULL)
	return (leaf_t *) NULL;

    if (in_order_str == NULL)
	return (leaf_t *) NULL;

    if (preIdx == NULL)
	return (leaf_t *) NULL;

    if ((start > end) || (start == end))
	return (leaf_t *) NULL;

    if (*preIdx == strlen(pre_order_str))
	return NULL;

    size_t bmax = 0;
    leaf_t * root = NULL;

    root = tr_create_leaf(pre_order_str[*preIdx]);
    *preIdx = *preIdx + 1;

    if ((end - start) > 1) {
	for(bmax = start; bmax < end; ++bmax)
	{
	    if(in_order_str[bmax] == root->data.c)
		break;
	}

	root->left = tr_rebuild_tree(pre_order_str, in_order_str, start, bmax, preIdx);
	root->right = tr_rebuild_tree(pre_order_str, in_order_str, bmax + 1, end, preIdx);
    }

    return root;
}
