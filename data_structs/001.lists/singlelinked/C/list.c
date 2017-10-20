#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "list.h"

list_t * list_init(void (*destroy) (void **), int32_t (*compare)(const void *, const void *), void (*print)(const void *)) {
    if (destroy == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return (list_t *) NULL;
    }
    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return (list_t *) NULL;
    }

    list_t *list = (list_t *) calloc(1, sizeof(list_t));

    if (list == (list_t *) NULL)
	return (list_t *) NULL;

    list->destroy = destroy;
    list->compare = compare;
    list->print = print;

    errno = LST_SUCCESS;
    return list;
}

void list_destroy(list_t **list) {
    if (*list == (list_t *) NULL)
	return;

    lst_element_t *element = (lst_element_t *) (*list)->head;
    lst_element_t *prev_element = (lst_element_t *) NULL;

    while (element != (lst_element_t *) NULL) {
	(*list)->destroy((void **) &(element->data));
	prev_element = element;
	element = element->next;

	memset(prev_element, 0x00, sizeof(lst_element_t));
	free(prev_element);
	prev_element = (lst_element_t *) NULL;
    }
    memset(*list, 0x00, sizeof(list_t));
    free(*list);
    *list = (list_t *) NULL;
}

lst_element_t * list_find_element(list_t *list, const void *data) {
    if (list == (list_t *) NULL) {
	errno = ERR_LST_NULL;
	return (lst_element_t *) NULL;
    }
    if (data == (void *) NULL) {
	errno = ERR_LST_ARGS_NULL;
	return (lst_element_t *) NULL;
    }

    lst_element_t * element = list->head;

    while (element != (lst_element_t *) NULL) {
	if (list->compare(element->data, data) == 0) {
	    return element;
	}
	element = element->next;
    }

    return (lst_element_t *) NULL;
}

int8_t list_ins_next(list_t *list, const void *element, const void *data) {
    if (list == (list_t *) NULL)
	return ERR_LST_NULL;

    lst_element_t * new_element = (lst_element_t *) calloc(1, sizeof(lst_element_t));
    lst_element_t * prev_element = (lst_element_t *) NULL;

    if (new_element == (lst_element_t *) NULL)
	return ERR_LST_MALLOC;

    new_element->data = (void *) data;

    /* if element == NULL it means we want to insert the new element
     * at the beginning of our list */
    if (element == (void *) NULL) {
	if (list->size == 0)
	    list->tail = new_element;
	new_element->next = list->head;
	list->head = new_element;
	++list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != (void *) NULL)
	    prev_element = list_find_element(list, element);

	if (prev_element != (lst_element_t *) NULL) {
	    if (prev_element->next == (lst_element_t *) NULL)
		list->tail = new_element;
	    new_element->next = prev_element->next;
	    prev_element->next = new_element;
	    ++list->size;
	} else {
	    memset(new_element, 0x00, sizeof(lst_element_t));
	    free(new_element);
	}
    }

    return LST_SUCCESS;
}

int8_t list_rem_next(list_t *list, const void * element, const void **data) {
    if (list == (list_t *) NULL)
	return ERR_LST_NULL;
    if (list->size == 0)
	return LST_EMPTY_LIST;

    lst_element_t * next_element = (lst_element_t *) NULL;
    lst_element_t * element_ptr = (lst_element_t *) NULL;

    /* if element == null we remove the head */
    if (element == (void *) NULL) {
	*data = list->head->data;
	next_element = list->head;
	list->head = next_element->next;
	--list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != (void *) NULL)
	    element_ptr = list_find_element(list, element);

	if ((element_ptr != (lst_element_t *) NULL) && (element_ptr->next != (lst_element_t *) NULL)) {
	    next_element = element_ptr->next;
	    *data = next_element->data;

	    if (next_element->next == (lst_element_t *) NULL)
		list->tail = element_ptr;

	    element_ptr->next = next_element->next;
	    --list->size;
	} else {
	    element_ptr = (lst_element_t *) NULL;
	    *data = (void *) NULL;}
    }

    if (list->size == 0)
	list->tail = list->head;

    if (next_element != (lst_element_t *) NULL) {
	memset(next_element, 0x00, sizeof(lst_element_t));
	free(next_element);
    }

    return LST_SUCCESS;
}

void list_print_elements(list_t *list) {
    if (list == (list_t *) NULL) {
	errno = ERR_LST_NULL;
	return;
    }
    if (list->size == 0) {
	errno = LST_EMPTY_LIST;
	return;
    }
    if (list->print == NULL) {
	errno = LST_FUNCTION_NULL;
	return;
    }

    lst_element_t * element = list->head;

    if (list->size > 0) {
	printf("[ ");
	while (element != (lst_element_t *) NULL) {
	    list->print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = LST_SUCCESS;
}
