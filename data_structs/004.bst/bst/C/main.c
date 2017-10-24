#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "bst.h"

int32_t main() {
    bst_tree_t * tree = bst_init(compare, destroy, print);

    data_t * data =  NULL;
    data_t * data_min = NULL;
    data_t * data_max = NULL;
    data_t * data_suc = NULL;
    data_t * data_pre = NULL;
    data_t * data_tmp = (data_t *) calloc(1, sizeof(*data));

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 54;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 27;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 17;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 41;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 19;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 23;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 37;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 47;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 83;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 71;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 67;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 68;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 69;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 91;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 90;
    bst_insert(tree, data);

    data = (data_t *) calloc(1, sizeof(*data));
    data->key = 99;
    bst_insert(tree, data);

    data_max = bst_find_max(tree);
    printf("Data found [max]: %d\n", data_max->key);

    data_min = bst_find_min(tree);
    printf("Data found [min]: %d\n", data_min->key);

    data_tmp->key = 17;
    data_suc = bst_find_suc(tree, data_tmp);
    if (data_suc != NULL) {
	    printf("Suc of %d is %d\n", data_tmp->key, data_suc->key);
    } else {
	printf("There is no suc of %d\n", data_tmp->key);
    }

    data_tmp->key = 54;
    data_pre = bst_find_pre(tree, data_tmp);
    if (data_pre != NULL) {
	    printf("Pre of %d is %d\n", data_tmp->key, data_pre->key);
    } else {
	printf("There is no pre of %d\n", data_tmp->key);
    }

    data_tmp->key = 17;
    bst_remove(tree, data_tmp);

    data_tmp->key = 71;
    bst_remove(tree, data_tmp);

    data_tmp->key = 83;
    bst_remove(tree, data_tmp);

    bst_print_tree(tree, PRE_ORDER);
    bst_destroy(&tree);

    memset(data_tmp, 0x00, sizeof(data_t));
    free(data_tmp);

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
    memset(tmp, 0x00, sizeof(data_t));
    free(tmp);
    *data = NULL;
}

void print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}

