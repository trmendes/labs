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
    int32_t  tail_id;
    node    *head;
    node    *tail;
} dllist;

dllist * dl_create            ();
int8_t   dl_destroy           (dllist **l);

void     dl_print             (dllist *l, char *headermsg, int32_t index, int8_t reverse);

int8_t   dl_insert_beginning  (dllist *l, int32_t value);
int8_t   dl_insert_end        (dllist *l, int32_t value);
int8_t   dl_insert_after      (dllist *l, int32_t key, int32_t value);
int8_t   dl_insert_before     (dllist *l, int32_t key, int32_t value);

int8_t   dl_remove_beginning  (dllist *l);
int8_t   dl_remove_end        (dllist *l);
int8_t   dl_remove_next       (dllist *l, int32_t key);
int8_t   dl_remove_prev       (dllist *l, int32_t key);

#endif
