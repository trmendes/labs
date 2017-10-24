#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "queue.h"

queue_t * queue_init(destroy_ft destroy, print_ft print) {
    if (destroy == NULL) {
	errno = QUEUE_ARGS_FAIL;
	return NULL;
    }

    queue_t *queue = (queue_t *) calloc(1, sizeof(*queue));

    if (queue == NULL)
	return NULL;

    queue->destroy = destroy;
    queue->print = print;

    errno = QUEUE_SUCCESS;
    return queue;
}

void queue_destroy(queue_t **queue) {
    if (*queue == NULL) {
	errno = QUEUE_NULL;
	return;
    }

    que_element_t *element = (que_element_t *) (*queue)->head;
    que_element_t *prev_element = NULL;

    while (element != NULL) {
	(*queue)->destroy((void **) &(element->data));
	prev_element = element;
	element = element->next;

	memset(prev_element, 0x00, sizeof(que_element_t));
	free(prev_element);
	prev_element = NULL;
    }
    memset(*queue, 0x00, sizeof(queue_t));
    free(*queue);
    *queue = NULL;
}

int8_t queue_add(queue_t *queue, const void *data) {
    if (queue == NULL)
	return QUEUE_NULL;

    que_element_t * new_element = (que_element_t *) calloc(1, sizeof(*new_element));

    if (new_element == NULL)
	return QUEUE_FAIL_MALLOC;

    new_element->data = (void *) data;

    if (queue->head == NULL) {
	queue->tail = new_element;
	queue->head = new_element;
    } else {
	queue->tail->next = new_element;
	queue->tail = new_element;
    }

    ++queue->len;

    return QUEUE_SUCCESS;
}

void * queue_get(queue_t *queue) {
    if (queue == NULL) {
	errno = QUEUE_NULL;
	return NULL;
    }
    if (queue->len == 0) {
	errno = QUEUE_EMPTY;
	return NULL;
    }

    void * data = NULL;
    que_element_t * new_tail = queue->head;

    while (new_tail->next != queue->tail) {
	new_tail = new_tail->next;
    }

    data = queue->tail->data;

    memset(queue->tail, 0x00, sizeof(que_element_t));
    free(queue->tail);
    queue->tail = NULL;

    queue->tail = new_tail;
    new_tail->next = NULL;

    --queue->len;

    if (queue->len == 0) {
	queue->tail = queue->head;
    }

    errno = QUEUE_SUCCESS;
    return data;
}

void queue_print_elements(queue_t *queue) {
    if (queue == NULL) {
	errno = QUEUE_NULL;
	return;
    }
    if (queue->len == 0) {
	errno = QUEUE_EMPTY;
	return;
    }
    if (queue->print == NULL) {
	errno = QUEUE_FUNCTION_NULL;
	return;
    }

    que_element_t * element = queue->head;

    if (queue->len > 0) {
	printf("[ ");
	while (element != NULL) {
	    queue->print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = QUEUE_SUCCESS;
}
