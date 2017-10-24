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

typedef int32_t (*compare_ft) (const void * const key1, const void * const key2);
typedef void    (*destroy_ft) (void **data);
typedef void    (*print_ft)   (const void * const data);

 typedef struct lst_element_s {
    void                 *data;
    struct lst_element_s *next;
    struct lst_element_s *prev;
} lst_element_t;

typedef struct list_s {
    size_t           size;
    compare_ft       compare;
    destroy_ft       destroy;
    print_ft         print;
    lst_element_t   *head;
    lst_element_t   *tail;
} list_t;

list_t *        dlist_init           (destroy_ft destroy, compare_ft compare, print_ft print);
void            dlist_destroy        (list_t **list);
lst_element_t * dlist_find_element   (list_t *list, const void *data);
int8_t          dlist_ins_next       (list_t *list, const void * element, const void *data);
int8_t          dlist_rem_next       (list_t *list, const void * element, const void **data);
int8_t          dlist_ins_prev       (list_t *list, const void * element, const void *data);
int8_t          dlist_rem_prev       (list_t *list, const void * element, const void **data);
void            dlist_print_elements (list_t *list);

#endif