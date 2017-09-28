#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bintree.h"

#define INSERT "inserir"
#define DELETE "excluir"
#define SEARCH "buscar"
#define MIN    "minimo"
#define MAX    "maximo"
#define POS    "pos-ordem"
#define IN     "em-ordem"
#define PRE    "pre-ordem"
#define WIDTH  "largura"
#define DONE   "terminar"

#define BUFMAX 100

int32_t main() {
    char cmd[BUFMAX];
    int32_t key, ret;

    leaf_t * r = (leaf_t *) NULL;
    leaf_t * tmp = (leaf_t *) NULL;

    while (1) {
	ret = scanf("%s ", cmd);
	if (ret == EOF)
	    break;

	if (strcmp(cmd, INSERT) == 0) {
	    scanf("%d", &key);
	    ret = tr_insert_by_value(&r, key);
	    if (ret == ERR_MALLOC)
		printf("memoria insuficiente\n");
	} else if (strcmp(cmd, DELETE) == 0) {
	    scanf("%d", &key);
	    tr_delete(&r, key);
	} else if (strcmp(cmd, SEARCH) == 0) {
	    scanf("%d", &key);
	    if (tr_find_leaf(r, key) == (leaf_t *) NULL)
		printf("nao pertence\n");
	    else
		printf("pertence\n");
	} else if (strcmp(cmd, MIN) == 0) {
	    tmp = tr_find_min(r);
	    if (tmp == (leaf_t *) NULL)
		printf("vazia\n");
	    else
		printf("%d\n", tmp->data.id);
	} else if (strcmp(cmd, MAX) == 0) {
	    tmp = tr_find_max(r);
	    if (tmp == (leaf_t *) NULL)
		printf("vazia\n");
	    else
		printf("%d\n", tmp->data.id);
	} else if (strcmp(cmd, POS) == 0) {
	    if (r == (leaf_t *) NULL)
		printf("vazia");
	    else
		tr_print(r, POS_ORDER);
	    printf("\n");
	} else if (strcmp(cmd, IN) == 0) {
	    if (r == (leaf_t *) NULL)
		printf("vazia");
	    else
		tr_print(r, IN_ORDER);
	    printf("\n");
	} else if (strcmp(cmd, PRE) == 0) {
	    if (r == (leaf_t *) NULL)
		printf("vazia");
	    else
		tr_print(r, PRE_ORDER);
	    printf("\n");
	} else if (strcmp(cmd, WIDTH) == 0) {
	} else if (strcmp(cmd, DONE) == 0) {
	    break;
	}
    }

    tr_destroy(r);

    return EXIT_SUCCESS;
}

