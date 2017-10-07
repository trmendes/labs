#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdint.h>

#define ERR_LCA_NOT_FOUND  -4
#define ERR_LEAF_NOT_FOUND -3
#define ERR_TREE_NULL      -2
#define ERR_FOREST_NULL    -1
#define SUCCESS             0

typedef struct data_s {
    int32_t    id;
} data_t;

typedef struct leaf_s {
    data_t          data;
    struct leaf_s * parent;
    uint8_t         flags;
} leaf_t;

typedef struct forestroot_s {
    leaf_t              *root;
    struct forestroot_s *next;
} forestroot_t;

typedef struct forest_s {;
    forestroot_t  * root;
    int32_t         size;
} forest_t;

int32_t       tr_insert_new_tree    (forest_t ** forest, int32_t rootKey);
leaf_t      * tr_find_tree_root     (forest_t * forest, int32_t key);
int32_t       tr_add_a_link         (forest_t * forest, int32_t rootKey, int32_t leafKey);
int32_t       tr_cut_a_link         (forest_t * forest, int32_t key);
int32_t       tr_lca                (forest_t * forest, int32_t keyA, int32_t keyB);
void          tr_destroy            (forest_t ** forest);

#endif