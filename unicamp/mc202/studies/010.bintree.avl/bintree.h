#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdint.h>

#define ERR_NO_LEAF    -4
#define ERR_MALLOC     -3
#define EMPTY_TREE     -2
#define ERR_TREE_NULL  -1
#define SUCCESS         0

#define AVL_MAX_LEFT   -2
#define AVL_MAX_RIGHT   2

typedef struct data_s {
    int32_t    id;
} data_t;

typedef struct leaf_s {
    data_t          data;
    struct leaf_s * left;
    struct leaf_s * right;
    struct leaf_s * parent;
    int8_t          avl_factor;
} leaf_t;

typedef enum printType {
    IN_ORDER = 1,
    PRE_ORDER = 2,
    POS_ORDER = 3,
} printType_e;

leaf_t    * tr_create             ();
void        tr_destroy            (leaf_t * root);
int32_t     tr_insert_by_value    (leaf_t **l, int32_t key);
leaf_t    * tr_find_leaf          (leaf_t *l , int32_t key);
leaf_t    * tr_find_min           (leaf_t *l);
leaf_t    * tr_find_max           (leaf_t *l);
leaf_t    * tr_find_pre           (leaf_t *l);
leaf_t    * tr_find_suc           (leaf_t *l);
int32_t     tr_delete             (leaf_t **l, int32_t key);
void        tr_print              (leaf_t * root, printType_e pType);
int32_t     tr_avl_rotete_left    (leaf_t ** root);
int32_t     tr_avl_rotete_right   (leaf_t ** root);

#endif