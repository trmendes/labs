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
} lst_element_t;

typedef struct list_s {
    size_t           size;
    lst_element_t   *head;
    lst_element_t   *tail;
} list_t;

list_t *        list_init           ();
void            list_destroy        (list_t **list, destroy_ft destroy);
void   *        list_lookup         (list_t *list, const void *data, compare_ft compare);
void   *        list_lookup_next    (list_t *list, const void *data, compare_ft compare);
int8_t          list_ins_next       (list_t *list, const void * element, const void *data, compare_ft compare);
int8_t          list_rem_next       (list_t *list, const void * element, const void **data, compare_ft compare_ft);
void            list_print_elements (list_t *list, print_ft print);

#endif