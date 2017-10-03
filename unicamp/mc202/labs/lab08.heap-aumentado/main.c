#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "heap.h"

#define INSERT "i"
#define NEWPRI "d"
#define MIN    "m"
#define DONE   "t"

#define BUFMAX 100

int32_t main() {
    char cmd[BUFMAX];
    int32_t key, pri, ret;
    size_t size;
    heap_ctrl_t *h = (heap_ctrl_t *) NULL;
    data_t * head = (data_t *) NULL;

    scanf("%lu", &size);

    h = hp_create(size);

    while (1) {
	ret = scanf("%s ", cmd);
	if (ret == EOF)
	    break;

	if (strcmp(cmd, INSERT) == 0) {
	    scanf("%d %d", &key, &pri);
	    hp_insert_min(h, key, pri);
	} else if (strcmp(cmd, NEWPRI) == 0) {
	    scanf("%d %d", &key, &pri);
	    hp_change_pri(h, key, pri);
	} else if (strcmp(cmd, MIN) == 0) {
	    head = hp_remove_min(h);
	    if (head == (data_t *) NULL)
		printf("vazio\n");
	    else {
		printf("minimo {%d,%d}\n", head->key, head->price);
		free(head);
		head = (data_t *) NULL;
	    }
	} else if (strcmp(cmd, DONE) == 0) {
	    break;
	}
    }

    hp_destroy(&h);

    return EXIT_SUCCESS;
}

