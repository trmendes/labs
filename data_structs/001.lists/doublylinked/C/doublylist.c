#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "doublylist.h"

list_t * dlist_init(destroy_ft destroy, compare_ft compare, print_ft print) {
    if (destroy == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }
    if (compare == NULL) {
	errno = ERR_LST_ARGS_NULL;
	return NULL;
    }

    list_t *list = calloc(1, sizeof(*list));

    if (list == NULL)
	return NULL;

    list->destroy = destroy;
    list->compare = compare;
    list->print = print;

    errno = LST_SUCCESS;
    return list;
}

void dlist_destroy(list_t **list) {
    if (*list == NULL) {
	errno = ERR_LST_NULL;
	return;
    }

    lst_element_t *element = (lst_element_t *) (*list)->head;
    lst_element_t *prev_element = NULL;

    while (element != NULL) {
	(*list)->destroy((void **) &(element->data));
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

lst_element_t * dlist_find_element(list_t *list, const void *data) {
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
	if (list->compare(element->data, data) == 0) {
	    return element;
	}
	element = element->next;
    }

    return NULL;
}

int8_t dlist_ins_next(list_t *list, const void *element, const void *data) {
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
	else
	    list->head->prev = new_element;
	new_element->next = list->head;
	new_element->prev = NULL;
	list->head = new_element;
	++list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    prev_element = dlist_find_element(list, element);

	if (prev_element != NULL) {
	    if (prev_element->next == NULL)
		list->tail = new_element; /* last element */
	    else
		prev_element->next->prev = new_element;
	    new_element->next = prev_element->next;
	    new_element->prev = prev_element;
	    prev_element->next = new_element;
	    ++list->size;
	} else {
	    memset(new_element, 0x00, sizeof(*new_element));
	    free(new_element);
	}
    }

    return LST_SUCCESS;
}

int8_t dlist_ins_prev(list_t *list, const void *element, const void *data) {
    if (list == NULL)
	return ERR_LST_NULL;

    lst_element_t * new_element = calloc(1, sizeof(*new_element));
    lst_element_t * next_element = NULL;

    if (new_element == NULL)
	return ERR_LST_MALLOC;

    new_element->data = (void *) data;

    /* if element == NULL it means we want to insert the new element
     * at the beginning of our list */
    if (element == NULL) {
	if (list->size == 0)
	    list->tail = new_element;
	else
	    list->head->prev = new_element;
	new_element->next = list->head;
	new_element->prev = NULL;
	list->head = new_element;
	++list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    next_element = dlist_find_element(list, element);

	if (next_element != NULL) {
	    if (next_element->prev == NULL) {
		new_element->next = list->head;
		list->head->prev = new_element;
		list->head = new_element; /* first element */
	    } else {
		new_element->next = next_element;
		new_element->prev = next_element->prev;
		next_element->prev->next = new_element;
		next_element->prev = new_element;
	    }
	    ++list->size;
	} else {
	    memset(new_element, 0x00, sizeof(*new_element));
	    free(new_element);
	}
    }

    return LST_SUCCESS;
}

int8_t dlist_rem_next(list_t *list, const void * element, const void **data) {
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
	    element_ptr = dlist_find_element(list, element);

	if ((element_ptr != NULL) && (element_ptr->next != NULL)) {
	    next_element = element_ptr->next;
	    *data = next_element->data;

	    /* prev_element is now the new tail */
	    if (next_element->next == NULL)
		list->tail = element_ptr;
	    else
		next_element->next->prev = element_ptr;

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

int8_t dlist_rem_prev(list_t *list, const void * element, const void **data) {
    if (list == NULL)
	return ERR_LST_NULL;
    if (list->size == 0)
	return LST_EMPTY_LIST;

    lst_element_t * prev_element = NULL;
    lst_element_t * element_ptr = NULL;

    /* if element == null we remove the head */
    if (element == NULL) {
	*data = list->head->data;
	prev_element = list->head;
	list->head = prev_element->next;
	--list->size;
    } else {
	/* double check if element lives inside of our list */
	/* It is necessary to avoid the use of a node that is
	 * not on our list */
	if (element != NULL)
	    element_ptr = dlist_find_element(list, element);

	if ((element_ptr != NULL) && (element_ptr->prev != NULL)) {
	    prev_element = element_ptr->prev;
	    *data = prev_element->data;

	    /* prev_element is now the new head */
	    if (prev_element->prev == NULL)
		list->head = element_ptr;
	    else
		prev_element->prev->next = element_ptr;

	    element_ptr->prev = prev_element->prev;

	    --list->size;
	} else {
	    element_ptr = NULL;
	    *data = NULL;}
    }

    if (list->size == 0)
	list->tail = list->head;

    if (prev_element != NULL) {
	memset(prev_element, 0x00, sizeof(*prev_element));
	free(prev_element);
    }

    return LST_SUCCESS;
}

void dlist_print_elements(list_t *list) {
    if (list == NULL) {
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
	while (element != NULL) {
	    list->print(element->data);
	    element = element->next;
	}
	printf("]\n");
    }

    errno = LST_SUCCESS;
}
