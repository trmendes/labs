#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "list.h"

int32_t main() {
    list_t * list = list_init(destroy, compare, print);
    data_t * data = NULL;
    data_t * dataprev = calloc(1, sizeof(*dataprev));
    data_t * remove = NULL;

    data = calloc(1, sizeof(*data));
    data->key = 1;
    list_ins_next(list, NULL, data);

    dataprev->key = 1;
    data = calloc(1, sizeof(*data));
    data->key = 2;
    list_ins_next(list, dataprev, data);

    dataprev->key = 2;
    data = calloc(1, sizeof(*data));
    data->key = 3;
    list_ins_next(list, dataprev, data);

    dataprev->key = 3;
    data = calloc(1, sizeof(*data));
    data->key = 4;
    list_ins_next(list, dataprev, data);

    dataprev->key = 4;
    data = calloc(1, sizeof(*data));
    data->key = 6;
    list_ins_next(list, dataprev, data);

    dataprev->key = 4;
    data = calloc(1, sizeof(*data));
    data->key = 5;
    list_ins_next(list, dataprev, data);

    data = calloc(1, sizeof(*data));
    data->key = 0;
    list_ins_next(list, NULL, data);

    list_print_elements(list);

    list_rem_next(list, NULL, (const void **) &remove);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list);

    dataprev->key = 4;
    list_rem_next(list, dataprev, (const void **) &remove);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    list_print_elements(list);

    dataprev->key = 3;
    list_rem_next(list, dataprev, (const void **) &remove);
    if (remove != NULL) {
	printf("Removed: %d\n", remove->key);
	free(remove);
	remove = NULL;
    }

    dataprev->key = 7;
    data = list_lookup(list, dataprev);
    if (data != NULL) {
	printf("%d is on the list [%d]\n", data->key, dataprev->key);
    } else {
	printf("%d isn't on the list\n", dataprev->key);
    }

    dataprev = NULL;
    data = list_lookup_next(list, dataprev);
    if (dataprev == NULL) {
	if (data == NULL) {
	    printf("Empty list\n");
	} else {
	    printf("First element of the list is: %d\n", data->key);
	}
    } else {
	if (data != NULL) {
	    printf("next of %d is %d\n", dataprev->key, data->key);
	} else {
	    printf("next of %d is NULL or %d does not exists\n", dataprev->key, dataprev->key);
	}
    }

    dataprev = NULL;
    while ((dataprev = list_lookup_next(list, dataprev)) != NULL) {
	    printf(" %d ", dataprev->key);
    }
    printf("\n");

    list_print_elements(list);

    free(dataprev);
    list_destroy(&list);

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

