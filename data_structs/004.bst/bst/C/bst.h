#ifndef __BST_H__
#define __BST_H__

#include <stdint.h>
#include <stdlib.h>

#define BST_EMPTY          -5
#define BST_DATA_NOT_FOUND -4
#define BST_NULL           -3
#define BST_FAIL_MALLOC    -2
#define BST_FAIL_ARGS      -1
#define BST_SUCCESS         0

typedef int32_t (*compare_ft) (const void * const dataA, const void * const dataB);
typedef void    (*destroy_ft) (void ** data);
typedef void    (*print_ft)   (const void * const data);

typedef enum {
    PRE_ORDER = 0x01,
    IN_ORDER = 0x02,
    POS_ORDER = 0x03
} bst_transversal_e;

typedef struct bst_leaf_s {
    void                 *data;
    struct bst_leaf_s    *parent;
    struct bst_leaf_s    *left;
    struct bst_leaf_s    *right;
} bst_leaf_t;

typedef struct bst_tree_s {
    bst_leaf_t       * root;
    compare_ft         compare;
    destroy_ft         destroy;
    print_ft           print;
} bst_tree_t;

bst_tree_t  * bst_init       (compare_ft compare, destroy_ft destroy, print_ft print);
int8_t        bst_insert     (bst_tree_t *tree, void *data);
int8_t        bst_remove     (bst_tree_t *tree, void *data);
void        * bst_find_data  (bst_tree_t *tree, void *data);
void        * bst_find_max   (bst_tree_t *tree);
void        * bst_find_min   (bst_tree_t *tree);
void        * bst_find_pre   (bst_tree_t *tree, void *data);
void        * bst_find_suc   (bst_tree_t *tree, void *data);
void          bst_destroy    (bst_tree_t **tree);
void          bst_print_tree (bst_tree_t const * const tree, const bst_transversal_e type);

#endif