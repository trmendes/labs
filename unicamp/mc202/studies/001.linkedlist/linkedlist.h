#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdint.h>

#define ERR_WRONG_RANGE  -6
#define CANT_FIND_NODE   -5
#define ERR_NULL_ARG     -4
#define ERR_NEED_MORE_EL -3
#define ERR_EMPT_LIST    -2
#define ERR_NULL_LIST    -1
#define SUCCESS           0

typedef struct snode {
    uint32_t      id;
    char         *cor;
    struct snode *next;
} node;

typedef struct slinkedlist {
    node     *head;
    uint32_t tail_id;
    uint32_t length;
} linkedlist;

linkedlist* ll_create                ();
int8_t      ll_destroy               (linkedlist **l);
linkedlist* ll_copylist              (linkedlist *l);
void        ll_print                 (linkedlist *l, int8_t index, char *extra);
int8_t      ll_insert_head           (linkedlist *l, char *color);
int8_t      ll_insert_tail           (linkedlist *l, char *color);
int8_t      ll_insert_at_index       (linkedlist *l, char *color, uint32_t index);
int8_t      ll_insert_tail_copy      (linkedlist *l, node *np);
int8_t      ll_remove_head           (linkedlist *l);
int8_t      ll_remove_tail           (linkedlist *l);
int8_t      ll_remove_tail_but_one   (linkedlist *l);
int8_t      ll_remove_specific_node  (linkedlist *l, node *p);
int8_t      ll_remove_specific_index (linkedlist *l, uint32_t index);
int8_t      ll_remove_specific_color (linkedlist *l, char *color);
int8_t      ll_remove_all_color      (linkedlist *l, char *color);
int8_t      ll_remove_min_id         (linkedlist *l);
node*       ll_get_index_node        (linkedlist *l, uint32_t index);
uint32_t    ll_len                   (linkedlist *l);
int8_t      ll_check_data            (linkedlist *l1, linkedlist *l2);
int8_t      ll_move_next_to_front    (linkedlist *l, node *p);

#endif