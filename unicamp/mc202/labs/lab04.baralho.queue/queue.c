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

    node_t *p = q->head;

    while (p != NULL) {
	q->head = p->next;
	free(p);
	p = q->head;;
    }

    q->len = 0;

    return SUCCESS;
}

int qe_insert(queue_t *q, node_t * data) {
    if (q == NULL)
	return ERR_QUEUE_NULL;

    if (q->head == NULL) {
	q->head = data;
	q->tail = data;
    } else {
	data->prev = NULL;
	data->next = q->head;
	q->head->prev = data;
	q->head = data;
    }

    q->len++;

    return SUCCESS;
}

node_t *qe_get(queue_t *q) {
    if (q == NULL)
	return NULL;
    if (q->head == NULL)
	return NULL;

    node_t *p = NULL;

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

    return p;
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

    node_t *p = q->tail;
    while (p != NULL) {
	printf("%d, ", p->id);
	p = p->prev;
    }
    printf("\b\b ");
}