#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "doublylist.h"

int32_t main() {
    list_t * list = dlist_init(destroy, compare, print);
    data_t * data = NULL;
    data_t * dataprev = calloc(1, sizeof(*dataprev));
    data_t * remove = NULL;

    data = calloc(1, sizeof(*data));
    data->key = 1;
    dlist_ins_prev(list, NULL, data);

    dataprev->key = 1;
    data = calloc(1, sizeof(*data));
    data->key = 2;
    dlist_ins_prev(list, dataprev, data);

    dataprev->key = 2;
    data = calloc(1, sizeof(*data));
    data->key = 3;
    dlist_ins_prev(list, dataprev, data);

    dataprev->key = 3;
    data = calloc(1, sizeof(*data));
    data->key = 4;
    dlist_ins_prev(list, dataprev, data);

    dataprev->key = 4;
    data = calloc(1, sizeof(*data));
    data->key = 6;
    dlist_ins_prev(list, dataprev, data);

    dataprev->key = 10;
    data = calloc(1, sizeof(*data));
    data->key = 5;
    dlist_ins_prev(list, NULL, data);

    data = calloc(1, sizeof(*data));
    data->key = 0;
    dlist_ins_prev(list, NULL, data);

    dlist_print_elements(list);

    dlist_rem_prev(list, NULL, (void **) &remove);
    if (remove != NULL) {
        printf("Removed: %d\n", remove->key);
        free(remove);
        remove = NULL;
    }

    dlist_print_elements(list);

    dataprev->key = 4;
    dlist_rem_prev(list, dataprev, (void **) &remove);
    if (remove != NULL) {
        printf("Removed: %d\n", remove->key);
        free(remove);
        remove = NULL;
    }

    dlist_print_elements(list);

    dataprev->key = 1;
    dlist_rem_prev(list, dataprev, (void **) &remove);
    if (remove != NULL) {
        printf("Removed: %d\n", remove->key);
        free(remove);
        remove = NULL;
    }

    dlist_print_elements(list);

    free(dataprev);
    dlist_destroy(&list);

    return EXIT_SUCCESS;
}

int32_t compare(void * key1, void * key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;

    return a->key - b->key;
}

void destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void print(void * data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}

