#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdint.h>

#define ERR_MALLOC     -3
#define EMPTY_TREE     -2
#define ERR_TREE_NULL  -1
#define SUCCESS         0

typedef struct data_s {
    int32_t    id;
} data_t;

typedef struct leaf_s {
    data_t          data;
    struct leaf_s * left;
    struct leaf_s * right;
    uint8_t         flags;
} leaf_t;

typedef struct tree_s {
    int32_t     len;
    leaf_t    * root;
} tree_t;

typedef enum printType {
    IN_ODER = 1,
} printType_e;

tree_t    * tr_create           ();
int32_t     tr_destroy          (tree_t * t);
int32_t     tr_insert_by_value  (tree_t * t, int32_t data);
void        tr_print            (leaf_t * root, printType_e pType);

#endif