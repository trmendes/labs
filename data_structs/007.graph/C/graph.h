#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>

#include "list.h"

#define GRAPH_VERTEX_NOT_FOUND -4
#define GRAPH_VERTEX_EXISTS    -3
#define GRAPH_FAIL_MALLOC      -2
#define GRAPH_ARGS_NULL        -1
#define GRAPH_SUCCESS           0

typedef lst_element_t node;

typedef int32_t (*compare_ft) (const void * const dataA, const void * const dataB);
typedef void    (*destroy_ft) (void ** data);
typedef void    (*print_ft)   (const void * const data);

typedef struct graph_s {
    size_t       vcounter;
    size_t       ecounter;
    list_t      *adjacents;
    compare_ft   compare;
    destroy_ft   destroy;
    print_ft     print;
} graph_t;

typedef struct graph_adj_s {
    void        *v;
    list_t      *adjacents;
} graph_adj_t;

graph_t    * graph_init     (compare_ft compare, destroy_ft destroy, print_ft print);
void         graph_destroy  (graph_t **);

int8_t       graph_ins_vert (graph_t *, const void *);
int8_t       graph_ins_edge (graph_t *, const void *, const void *);

int8_t       graph_rem_vert (graph_t *, void **);
int8_t       graph_rem_edge (graph_t *, const void *, const void *);

int32_t      graph_vcount   (graph_t *);
int32_t      graph_ecount   (graph_t *);

#endif