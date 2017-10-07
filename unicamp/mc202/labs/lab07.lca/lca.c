#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lca.h"
#include "queue.h"

int32_t tr_insert_new_tree(forest_t ** forest, int32_t rootKey) {

    forestroot_t *froot = (forestroot_t *) calloc(1, sizeof(forestroot_t));
    froot->root = (leaf_t *) calloc(1, sizeof(leaf_t));
    froot->root->data.id = rootKey;
    froot->root->parent = froot->root;

    if (*forest == (forest_t *) NULL) {
	forest_t * forestroot = (forest_t *) calloc(1, sizeof(forest_t));
	*forest = forestroot;
	(*forest)->root = froot;
    }
    else {

	forestroot_t * p = (*forest)->root;

	while (p->next != NULL)
	    p = p->next;

	p->next = froot;
    }

    ++(*forest)->size;

    return SUCCESS;
}

leaf_t * tr_find_tree_root(forest_t * forest, int32_t key) {
    if (forest == (forest_t *) NULL)
	return (leaf_t *) NULL;

    if (forest->root == (forestroot_t *) NULL)
	return (leaf_t *) NULL;

    forestroot_t * p = forest->root;

    while (p != NULL) {
	if (p->root->data.id == key)
	    break;
	p = p->next;
    }

    if (forest == (forest_t *) NULL)
	return (leaf_t *) NULL;
    else
	return p->root;
}

int32_t tr_add_a_link(forest_t * forest, int32_t rootKey, int32_t leafKey) {
    if (forest == (forest_t *) NULL)
	return ERR_FOREST_NULL;

    if (forest->root == (forestroot_t *) NULL)
	return ERR_TREE_NULL;

    leaf_t * root = tr_find_tree_root(forest, rootKey);

    if (root == (leaf_t *) NULL)
	return ERR_LEAF_NOT_FOUND;

    leaf_t * leaf = tr_find_tree_root(forest, leafKey);

    if (leaf == (leaf_t *) NULL)
	return ERR_LEAF_NOT_FOUND;

    leaf->parent = root;

    return SUCCESS;
}

int32_t tr_cut_a_link(forest_t * forest, int32_t key) {
    if (forest == (forest_t *) NULL)
	return ERR_FOREST_NULL;

    leaf_t * root = tr_find_tree_root(forest, key);

    if (root != (leaf_t *) NULL)
	root->parent = (leaf_t *) NULL;

    return SUCCESS;
}

int32_t tr_lca(forest_t * forest, int32_t keyA, int32_t keyB) {
    if (forest == (forest_t *) NULL)
	return ERR_FOREST_NULL;

    queue_t * queue = qe_create();
    int32_t lca;
    int32_t j;
    leaf_t * rootA = tr_find_tree_root(forest, keyA);
    leaf_t * rootB = tr_find_tree_root(forest, keyB);

    if (rootA == rootB)
	return rootA->data.id;

    while (1) {
	if (rootA == (leaf_t *) NULL)
	    break;
	qe_insert(queue, rootA->data.id);
	if (rootA->parent == rootA)
	    break;
	rootA = rootA->parent;
    }

    while (1) {
	if (rootB == (leaf_t *) NULL)
	    break;
	j = qe_len(queue);
	while (j >= 0) {
	    lca = qe_get(queue);
	    --j;
	    if (lca == rootB->data.id) {
		qe_destroy(queue);
		return lca;
	    }
	    qe_insert(queue, lca);
	}
	if (rootB->parent == rootB)
	    break;
	rootB = rootB->parent;
    }

    qe_destroy(queue);

    return ERR_LEAF_NOT_FOUND;
}

void tr_destroy(forest_t ** forest) {
    if (*forest == (forest_t *) NULL)
	return;
}