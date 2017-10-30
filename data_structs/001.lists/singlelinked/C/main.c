#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "list.h"

int32_t main() {
    list_t * list = list_init();
    data_t * data = NULL;
    data_t * dataprev = calloc(1, sizeof(*dataprev));
    data_t * remove = NULL;

    data = calloc(1, sizeof(*data));
    data->key = 1;
    list_ins_next(list, NULL, data, compare);

    dataprev->key = 1;
    data = calloc(1, sizeof(*data));
    data->key = 2;
    list_ins_next(list, dataprev, data, compare);

    dataprev->key = 2;
    data = calloc(1, sizeof(*data));
    data->key = 3;
    list_ins_next(list, dataprev, data, compare);

    dataprev->key = 3;
    data = calloc(1, sizeof(*data));
    data->key = 4;
    list_ins_next(list, dataprev, data, compare);

    dataprev->key = 4;
    data = calloc(1, sizeof(*data));
    data->key = 6;
    list_ins_next(list, dataprev, data, compare);

    dataprev->key = 4;
    data = calloc(1, sizeof(*data));
    data->key = 5;
    list_ins_next(list, dataprev, data, compare);

    data = calloc(1, sizeof(*data));
    data->key = 0;
    list_ins_next(list, NULL, data, compare);

    list_print_elements(list, print);

    list_rem_next(list, NULL, (const void **) &remove, compare);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list, print);

    dataprev->key = 4;
    list_rem_next(list, dataprev, (const void **) &remove, compare);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list, print);

    dataprev->key = 3;
    list_rem_next(list, dataprev, (const void **) &remove, compare);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    dataprev->key = 7;
    data = list_lookup(list, dataprev, compare);
    if (data != NULL) {
	printf("%d is on the list [%d]\n", data->key, dataprev->key);
    } else {
	printf("%d isn't on the list\n", dataprev->key);
    }

    data = NULL;
    while ((data = list_lookup_next(list, data, compare)) != NULL) {
	    printf(" %d ", data->key);
    }
    printf("\n");

    list_print_elements(list, print);

    free(dataprev);
    list_destroy(&list, destroy);

    return EXIT_SUCCESS;
}

int32_t compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    if (a->key == b->key)
	return 0;
    if (a->key < b->key)
	return -1;
    if (a->key > b->key)
	return 1;

    return 0;
}

void destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}

