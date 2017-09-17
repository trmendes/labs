#include "bintree.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int32_t main() {
    char prb[BMAX] = { 0 };
    char inb[BMAX] = { 0 };
    int32_t read = 0;
    size_t preIdx = 0;

    while (1) {
	memset(&prb, 0, BMAX);
	memset(&inb, 0, BMAX);
	read = scanf("%s %s", prb, inb);
	if (read == EOF)
	    break;

	preIdx = 0;
	leaf_t * root = tr_rebuild_tree(prb, inb, 0, strlen(prb), &preIdx);
	tr_print_pos(root);
	tr_destroy(root);
	printf("\n");
    }

    return EXIT_SUCCESS;
}
