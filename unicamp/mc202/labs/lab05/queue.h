#ifndef __QUEUE_H__
#define __QUEUE_H__

#define ERR_QUEUE_NULL   -1
#define ERR_QUEUE_EMPTY  -2
#define ERR_QUEUE_MALLOC -3
#define SUCCESS           0

typedef struct qe_node_s {
    int                id;
    struct qe_node_s * next;
    struct qe_node_s * prev;
} qe_node_t;

typedef struct queue_s {
    int         len;
    qe_node_t * head;
    qe_node_t * tail;
} queue_t;

queue_t * qe_create    ();
int       qe_destroy   (queue_t *q);
int       qe_insert    (queue_t *q, int data);
int       qe_get       (queue_t *q);
int       qe_len       (queue_t *q);
void      qe_print     (queue_t *q);

#endif
