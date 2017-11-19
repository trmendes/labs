#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>
#include <limits.h>

#include "list.h"

#define GRAPH_ADJ_EXISTS       -5
#define GRAPH_VERTEX_NOT_FOUND -4
#define GRAPH_VERTEX_EXISTS    -3
#define GRAPH_FAIL_MALLOC      -2
#define GRAPH_ARGS_NULL        -1
#define GRAPH_SUCCESS           0

#define GRAPH_VERTEX_VISTED     1
#define GRAPH_VERTEX_NVISITED   0

#define GRAPH_EDGE_DUAL         1
#define GRAPH_EDGE_NDUAL        0

#define GRAPH_INFINIT INT_MAX

typedef list_t adj_list_t;

typedef int32_t (*compare_ft) (const void * const data_a, const void * const data_b);
typedef void    (*destroy_ft) (void ** data);
typedef void    (*print_ft)   (const void * const data);

typedef struct graph_api_s {
    print_ft            print;
} graph_api_t;

typedef struct graph_s {
    list_t             *vertexs;
    int32_t             vcnt;
    int32_t             ecnt;
    graph_api_t         api;
} graph_t;

typedef struct graph_vertex_s graph_vertex_t;

typedef struct graph_info_s {
    uint8_t             status;
    int32_t             distance;
    int32_t             degree;
    graph_vertex_t    * parent;
} graph_info_t;

typedef struct graph_vertex_s {
    void               *v;
    list_t             *edges;
    graph_info_t        info;
} graph_vertex_t;

typedef struct graph_edge_s {
    int32_t             cost;
    graph_vertex_t    * vertex;
    graph_vertex_t    * incident;
} graph_edge_t;

graph_t    * graph_init               (print_ft print);
void         graph_destroy            (graph_t **);

int8_t       graph_ins_vert           (graph_t *, const void *);
int8_t       graph_ins_edge           (graph_t *, const void *, const void *, int32_t, int8_t);

int8_t       graph_rem_vert           (graph_t *, void **);
int8_t       graph_rem_edge           (graph_t *, const void *, const void *);

int32_t      graph_vcount             (graph_t *);
int32_t      graph_ecount             (graph_t *);

int32_t      graph_bfs                (graph_t *, void *);
int32_t      graph_dijkstra           (graph_t *, void *, adj_list_t *);
int32_t      graph_mst_prism          (graph_t *, void *);

void         graph_print_vertexes     (graph_t *);
#endif