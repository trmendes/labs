#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "list.h"

int32_t main() {
    list_t * list = list_init(destroy, compare, print);
    data_t * data = (data_t *) NULL;
    data_t * dataprev = (data_t *) calloc(1, sizeof(data_t));
    data_t * remove = (data_t *) NULL;

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 1;
    list_ins_next(list, NULL, data);

    dataprev->key = 1;
    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 2;
    list_ins_next(list, dataprev, data);

    dataprev->key = 2;
    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 3;
    list_ins_next(list, dataprev, data);

    dataprev->key = 3;
    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 4;
    list_ins_next(list, dataprev, data);

    dataprev->key = 4;
    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 6;
    list_ins_next(list, dataprev, data);

    dataprev->key = 4;
    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 5;
    list_ins_next(list, dataprev, data);

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 0;
    list_ins_next(list, NULL, data);

    list_print_elements(list);

    list_rem_next(list, NULL, (const void **) &remove);
    if (remove != (data_t *) NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list);

    dataprev->key = 4;
    list_rem_next(list, dataprev, (const void **) &remove);
    if (remove != (data_t *) NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list);

    dataprev->key = 3;
    list_rem_next(list, dataprev, (const void **) &remove);
    if (remove != (data_t *) NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list);

    free(dataprev);
    list_destroy(&list);

    return EXIT_SUCCESS;
}

int32_t compare(const void *key1, const void *key2) {
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
    memset(tmp, 0x00, sizeof(data_t));
    free(tmp);
    *data = (void *) NULL;
}

void print(const void *data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}

