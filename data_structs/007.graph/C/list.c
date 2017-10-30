#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "list.h"

/* Private Prototypes */
lst_element_t * list_find_element(list_t *list, const void *data, compare_ft compare);

list_t * list_init() {

    list_t *list = calloc(1, sizeof(*list));

    if (list == NULL)
	return NULL;

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

void * list_lookup(list_t *list, const void *data, compare_ft compare) {
    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    if (list == NULL) {
	errno = ERR_LST_NULL;
	return NULL;
    }
    if (data == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    lst_element_t * element = list_find_element(list, data, compare);

    if (element == NULL)
	return NULL;

    return element->data;
}

void *list_lookup_next(list_t *list, const void *data, compare_ft compare) {
    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return NULL;
    }

    void * retdata = NULL;
    lst_element_t * element = NULL;

    if ((data == NULL) && (list->head != NULL)) {
	retdata = list->head->data;
    } else if (data != NULL) {
	element = list_find_element(list, data, compare);
	if (element != NULL)
	    if (element->next != NULL)
		retdata = element->next->data;
    }

    errno = LST_SUCCESS;

    return retdata;
}

lst_element_t * list_find_element(list_t *list, const void *data, compare_ft compare) {
    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }
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
	if (compare(element->data, data) == 0) {
	    return element;
	}
	element = element->next;
    }

    return NULL;
}

int8_t list_ins_next(list_t *list, const void *element, const void *data, compare_ft compare) {
    if (list == NULL)
	return ERR_LST_NULL;

    lst_element_t * new_element = calloc(1, sizeof(*new_element));
    lst_element_t * prev_element = NULL;

    if (new_element == NULL)
	return ERR_LST_MALLOC;

    new_element->data = (void *) data;

    /* if element == NULL it means we want to insert the new element
     * at the beginning of our list */
    if (element == NULL) {
	if (list->size == 0)
	    list->tail = new_element;
	new_element->next = list->head;
	list->head = new_element;
	++list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    prev_element = list_find_element(list, element, compare);

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

int8_t list_rem_next(list_t *list, const void * element, const void **data, compare_ft compare) {
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
	    element_ptr = list_find_element(list, element, compare);

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

void list_print_elements(list_t *list, print_ft print) {
    if (list == NULL) {
	errno = ERR_LST_NULL;
	return;
    }
    if (list->size == 0) {
	errno = LST_EMPTY_LIST;
	return;
    }
    if (print == NULL) {
	errno = LST_FUNCTION_NULL;
	return;
    }

    lst_element_t * element = list->head;

    if (list->size > 0) {
	printf("[ ");
	while (element != NULL) {
	    print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = LST_SUCCESS;
}
