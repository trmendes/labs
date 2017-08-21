#ifndef _D_L_LIST_H_
#define _D_L_LIST_H_

#include <stdint.h>

#define SUCCESS          0
#define ERR_NO_LIST     -1
#define ERR_EMPTY_LIST  -2
#define ERR_MALLOC_FAIL -3

typedef struct snode {
    int32_t       id;
    int32_t       data;
    struct snode *next;
    struct snode *prev;
} node;

typedef struct sdllist {
    int32_t  len;
    int32_t  last_id;
    node    *first;
    node    *last;
} dllist;

dllist * dl_create            ();
int8_t   dl_destory           (dllist **l);

void     dl_print             (dllist *l, char *headermsg, int32_t index, int8_t reverse);

int8_t   dl_insert_beginning  (dllist *l, int32_t value);
int8_t   dl_insert_end        (dllist *l, int32_t value);
int8_t   dl_insert_after      (dllist *l, int32_t value);
int8_t   dl_insert_before     (dllist *l, int32_t value);

int8_t   dl_remove_beginning  (dllist *l);
int8_t   dl_remove_end        (dllist *l);
int8_t   dl_remove_next       (dllist *l, int32_t id);
int8_t   dl_remove_prev       (dllist *l, int32_t id);
int8_t   dl_remove_all_values (dllist *l, int32_t value);
int8_t   dl_remove            (dllist *l, int32_t id);

node   * dl_get_node          (dllist *l, int32_t value);

#endif
