#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>
#include <stdlib.h>

#define LST_FUNCTION_NULL    -6
#define LST_EMPTY_LIST       -5
#define ERR_LST_ARGS_NULL    -4
#define ERR_LST_MALLOC       -3
#define ERR_LST_NULL         -2
#define ERR_LST_DESTROY_NULL -1
#define LST_SUCCESS           0

typedef struct lst_element_s {
    void                 *data;
    struct lst_element_s *next;
    struct lst_element_s *prev;
} lst_element_t;

typedef struct list_s {
    size_t           size;
    int32_t          (*compare) (const void *key1, const void *key2);
    void             (*destroy) (void **data);
    void             (*print)   (const void *data);
    lst_element_t   *head;
    lst_element_t   *tail;
} list_t;

list_t *        dlist_init           (void (*destroy)(void **), int32_t (*compare)(const void *, const void *), void (*print)(const void *));
void            dlist_destroy        (list_t **list);
lst_element_t * dlist_find_element   (list_t *list, const void *data);
int8_t          dlist_ins_next       (list_t *list, const void * element, const void *data);
int8_t          dlist_rem_next       (list_t *list, const void * element, const void **data);
int8_t          dlist_ins_prev       (list_t *list, const void * element, const void *data);
int8_t          dlist_rem_prev       (list_t *list, const void * element, const void **data);
void            dlist_print_elements (list_t *list);

#endif