#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdint.h>
#include<stdlib.h>

#define ERR_MALLOC     -3
#define EMPTY_TREE     -2
#define ERR_TREE_NULL  -1
#define SUCCESS         0

#define BMAX 1000

typedef struct data_s {
    int32_t    id;
    char       c;
} data_t;

typedef struct leaf_s {
    data_t          data;
    struct leaf_s * left;
    struct leaf_s * right;
    struct leaf_s * parent;
    uint8_t         flags;
} leaf_t;

leaf_t    * tr_find_leaf          (leaf_t *l, int32_t key);
void        tr_print_pre          (leaf_t * root);
void        tr_print_in           (leaf_t * root);
void        tr_print_pos          (leaf_t * root);
void        tr_destroy            (leaf_t *root);
leaf_t    * tr_rebuild_tree       (char * pre_order_str, char * in_order_str, size_t start, size_t end, size_t * preIdx);
leaf_t    * tr_create_leaf        (char c);

#endif