#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

queue_t * qe_create() {
    queue_t * q = calloc(1, sizeof(queue_t));
    return q;
}

int qe_destroy(queue_t *q) {
    if (q == NULL)
	return ERR_QUEUE_NULL;

    qe_node_t *p = q->head;

    while (p != NULL) {
	q->head = p->next;
	free(p);
	p = q->head;;
    }

    q->len = 0;

    return SUCCESS;
}

int qe_insert(queue_t *q, int data) {
    if (q == NULL)
	return ERR_QUEUE_NULL;

    qe_node_t * node = calloc(1, sizeof(qe_node_t));
    
    if (node == NULL)
	return ERR_QUEUE_MALLOC;

    node->id = data;

    if (q->head == NULL) {
	q->head = node;
	q->tail = node;
    } else {
	node->prev = NULL;
	node->next = q->head;
	q->head->prev = node;
	q->head = node;
    }

    q->len++;

    return SUCCESS;
}

int qe_get(queue_t *q) {
    if (q == NULL)
	return ERR_QUEUE_NULL;
    if (q->head == NULL)
	return ERR_QUEUE_EMPTY;

    int data;
    qe_node_t *p = NULL;

    if (q->head == q->tail) {
	p = q->tail;
	q->head = NULL;
	q->tail = NULL;
    } else {
	p = q->tail;
	q->tail->prev->next = NULL;
	q->tail = q->tail->prev;
	p->prev = NULL;
    }

    q->len--;

    data = p->id;
    free(p);

    return data;
}

int qe_len(queue_t *q) {
    if (q == NULL)
	return ERR_QUEUE_NULL;

    return q->len;
}

void qe_print(queue_t *q) {
    if (q == NULL)
	return;
    if (q->head == NULL)
	return;

    qe_node_t *p = q->head;
    while (p != NULL) {
	printf("[%d] ", p->id);
	p = p->next;
    }
    printf("\n");
}