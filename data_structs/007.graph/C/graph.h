#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>

#include "list.h"

#define GRAPH_ADJ_EXISTS       -5
#define GRAPH_VERTEX_NOT_FOUND -4
#define GRAPH_VERTEX_EXISTS    -3
#define GRAPH_FAIL_MALLOC      -2
#define GRAPH_ARGS_NULL        -1
#define GRAPH_SUCCESS           0

#define GRAPH_BFS_VISTED        1
#define GRAPH_BFS_NVISITED      0

typedef list_t adj_list_t;

typedef int32_t (*compare_ft) (const void * const data_a, const void * const data_b);
typedef void    (*destroy_ft) (void ** data);
typedef void    (*print_ft)   (const void * const data);

typedef struct graph_api_s {
    print_ft            print;
} graph_api_t;

typedef struct graph_s {
    size_t              vcounter;
    size_t              ecounter;
    list_t             *vertexs;
    graph_api_t         api;
} graph_t;

typedef struct graph_vertex_s graph_vertex_t;

typedef struct graph_bfs_s {
    uint8_t             status;
    int32_t             distance;
    graph_vertex_t    * parent;
} graph_bfs_t;

typedef struct graph_vertex_s {
    void               *v;
    list_t             *adjacents;
    graph_bfs_t         bfs;
} graph_vertex_t;

graph_t    * graph_init               (print_ft print);
void         graph_destroy            (graph_t **);

int8_t       graph_ins_vert           (graph_t *, const void *);
int8_t       graph_ins_edge           (graph_t *, const void *, const void *);

int8_t       graph_rem_vert           (graph_t *, void **);
int8_t       graph_rem_edge           (graph_t *, const void *, const void *);

int32_t      graph_vcount             (graph_t *);
int32_t      graph_ecount             (graph_t *);

void       * graph_lookup_next_vertex (graph_t * graph, void * data);

int32_t      graph_bfs                (graph_t * graph, void * start_point);

#endif