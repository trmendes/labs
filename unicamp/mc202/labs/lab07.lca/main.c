#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lca.h"

#define LINK   "link"
#define CUTCMD "cut"
#define LCA    "lca"

#define BUFMAX 100

int32_t main() {
    char cmd[BUFMAX];
    int32_t a, b, n, turns, i, ret, lca;

    forest_t * f = (forest_t *) NULL;

    while (1) {
	ret = scanf("%d %d ", &n, &turns);

	if (ret == EOF)
	    break;

	for (i = 1; i <= n; ++i) {
	    tr_insert_new_tree(&f, i);
	}

	for (i = 0; i < turns; ++i) {
	    scanf("%s ", cmd);

	    if (strcmp(cmd, LINK) == 0) {
		scanf("%d %d", &a, &b);
		//printf("LINK %d %d\n", a, b);
		tr_add_a_link(f, b, a);
	    } else if (strcmp(cmd, CUTCMD) == 0) {
		scanf("%d", &a);
		//printf("CUTCMD %d\n", a);
		tr_cut_a_link(f, a);
	    } else if (strcmp(cmd, LCA) == 0) {
		scanf("%d %d", &a, &b);
		//printf("LCA %d %d\n", a, b);
		lca = tr_lca(f, a, b);
		printf("%d\n", lca);
	    }
	}

	//tr_destroy(&f);

    }


    return EXIT_SUCCESS;
}

