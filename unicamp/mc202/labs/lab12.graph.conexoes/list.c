#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "list.h"

/* Private Prototypes */
lst_element_t * list_find_element(list_t *list, const void *data);

list_t * list_init(compare_ft compare, print_ft print) {

    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    list_t *list = calloc(1, sizeof(*list));

    if (list == NULL) {
	errno = ERR_LST_MALLOC;
	return NULL;
    }

    list->api.compare = compare;
    list->api.print = print;

    errno = LST_SUCCESS;
    return list;
}

void list_destroy(list_t **list, destroy_ft destroy) {
    if (*list == NULL) {
	errno = ERR_LST_NULL;
	return;
    }

    lst_element_t *element = (lst_element_t *) (*list)->head;
    lst_element_t *prev_element = NULL;

    while (element != NULL) {
	if (destroy != NULL)
	    destroy((void **) &(element->data));
	prev_element = element;
	element = element->next;

	memset(prev_element, 0x00, sizeof(*prev_element));
	free(prev_element);
	prev_element = NULL;
    }

    memset(*list, 0x00, sizeof(**list));
    free(*list);
    *list = NULL;
    errno = LST_SUCCESS;
}

void * list_lookup(list_t *list, const void *data) {
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return NULL;
    }
    if (data == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    lst_element_t * element = list_find_element(list, data);

    if (element == NULL)
	return NULL;

    return element->data;
}

void *list_lookup_next(list_t *list, const void *data) {
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return NULL;
    }

    void * retdata = NULL;
    lst_element_t * element = NULL;

    if ((data == NULL) && (list->head != NULL)) {
	retdata = list->head->data;
    } else if (data != NULL) {
	element = list_find_element(list, data);
	if (element != NULL)
	    if (element->next != NULL)
		retdata = element->next->data;
    }

    errno = LST_SUCCESS;

    return retdata;
}

lst_element_t * list_find_element(list_t *list, const void *data) {
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return NULL;
    }
    if (data == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    lst_element_t * element = list->head;

    while (element != NULL) {
	if (list->api.compare(element->data, data) == 0) {
	    return element;
	}
	element = element->next;
    }

    return NULL;
}

int8_t list_ins_next(list_t *list, const void *element, const void *data) {
    if (list == NULL)
	return ERR_LST_NULL;

    lst_element_t * new_element = calloc(1, sizeof(*new_element));
    lst_element_t * prev_element = NULL;

    if (new_element == NULL)
	return ERR_LST_MALLOC;

    new_element->data = (void *) data;

    /* if element == NULL it means we want to insert the new element
     * at the tail of our list */
    if (element == NULL) {
	if (list->size == 0) {
	    list->tail = new_element;
	    list->head = new_element;
	} else{
	    list->tail->next = new_element;
	    list->tail = new_element;
	}
	++list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    prev_element = list_find_element(list, element);

	if (prev_element != NULL) {
	    if (prev_element->next == NULL)
		list->tail = new_element;
	    new_element->next = prev_element->next;
	    prev_element->next = new_element;
	    ++list->size;
	} else {
	    memset(new_element, 0x00, sizeof(*new_element));
	    free(new_element);
	}
    }

    return LST_SUCCESS;
}

int8_t list_ins_in_order(list_t *list, const void *data) {
    if (list == NULL)
	return ERR_LST_NULL;

    lst_element_t * new_element = calloc(1, sizeof(*new_element));
    lst_element_t * element = NULL;
    lst_element_t * prev_element = NULL;

    if (new_element == NULL)
	return ERR_LST_MALLOC;

    new_element->data = (void *) data;

    element = list->head;
    prev_element = list->head;

    while (element != NULL) {
	if (list->api.compare(data, element->data) >= 0)
	    prev_element = element;
	else
	    break;
	element = element->next;
    }

    if (prev_element == NULL) {
	list->head = new_element;
	list->tail = new_element;
    } else {
	if (prev_element == list->head) {
	    if (list->api.compare(data, prev_element->data) >= 0) {
		new_element->next = prev_element->next;
		prev_element->next = new_element;
	    } else {
		list->head = new_element;
		new_element->next = prev_element;
	    }
	} else {
	    new_element->next = prev_element->next;
	    prev_element->next = new_element;
	}

	if (element == NULL)
	    list->tail = new_element;
    }

    ++list->size;

    return LST_SUCCESS;
}

int8_t list_rem_next(list_t *list, const void * element, const void **data) {
    if (list == NULL)
	return ERR_LST_NULL;
    if (list->size == 0)
	return LST_EMPTY_LIST;

    lst_element_t * next_element = NULL;
    lst_element_t * element_ptr = NULL;

    /* if element == null we remove the head */
    if (element == NULL) {
	*data = list->head->data;
	next_element = list->head;
	list->head = next_element->next;
	--list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    element_ptr = list_find_element(list, element);

	if ((element_ptr != NULL) && (element_ptr->next != NULL)) {
	    next_element = element_ptr->next;
	    *data = next_element->data;

	    if (next_element->next == NULL)
		list->tail = element_ptr;

	    element_ptr->next = next_element->next;
	    --list->size;
	} else {
	    element_ptr = NULL;
	    *data = NULL;}
    }

    if (list->size == 0)
	list->tail = list->head;

    if (next_element != NULL) {
	memset(next_element, 0x00, sizeof(*next_element));
	free(next_element);
    }

    return LST_SUCCESS;
}

void list_print_elements(list_t *list) {
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return;
    }
    if (list->size == 0) {
	errno = LST_EMPTY_LIST;
	return;
    }
    if (list->api.print == NULL) {
	errno = LST_FUNCTION_NULL;
	return;
    }

    lst_element_t * element = list->head;

    if (list->size > 0) {
	printf("[ ");
	while (element != NULL) {
	    list->api.print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = LST_SUCCESS;
}
