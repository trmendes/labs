#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "queue.h"

queue_t * queue_init() {
    queue_t *queue = calloc(1, sizeof(*queue));

    if (queue == NULL)
	return NULL;

    errno = QUEUE_SUCCESS;
    return queue;
}

void queue_destroy(queue_t **queue, destroy_ft destroy) {
    if (*queue == NULL) {
	errno = QUEUE_NULL;
	return;
    }

    que_element_t *element = (que_element_t *) (*queue)->head;
    que_element_t *prev_element = NULL;

    while (element != NULL) {
	if (destroy != NULL)
	    destroy((void **) &(element->data));
	prev_element = element;
	element = element->next;

	memset(prev_element, 0x00, sizeof(*prev_element));
	free(prev_element);
	prev_element = NULL;
    }
    memset(*queue, 0x00, sizeof(**queue));
    free(*queue);
    *queue = NULL;
}

int8_t queue_add(queue_t *queue, const void *data) {
    if (queue == NULL)
	return QUEUE_NULL;

    que_element_t * new_element = calloc(1, sizeof(*new_element));

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

    que_element_t * new_head = NULL;

    void * data = NULL;

    data = queue->head->data;

    new_head = queue->head->next;

    memset(queue->head, 0x00, sizeof(*(queue->head)));
    free(queue->head);
    queue->head = NULL;

    queue->head = new_head;

    --queue->len;

    if (queue->len == 0) {
	queue->tail = queue->head;
    }

    errno = QUEUE_SUCCESS;
    return data;
}

void queue_print_elements(queue_t *queue, print_ft print) {
    if (queue == NULL) {
	errno = QUEUE_NULL;
	return;
    }
    if (queue->len == 0) {
	errno = QUEUE_EMPTY;
	return;
    }
    if (print == NULL) {
	errno = QUEUE_FUNCTION_NULL;
	return;
    }

    que_element_t * element = queue->head;

    if (queue->len > 0) {
	printf("[ ");
	while (element != NULL) {
	    print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = QUEUE_SUCCESS;
}
