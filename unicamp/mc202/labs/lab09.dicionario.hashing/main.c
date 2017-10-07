#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"

#define INSERT "i"
#define FIND   "b"
#define REMOVE "r"
#define DONE   "f"

#define BUFMAX 250

int32_t main() {
    char cmd[BUFMAX];
    char data[BUFMAX];
    int32_t ret;

    hash_t * h = hs_create(6007);

    while (1) {
	ret = scanf("%s ", cmd);
	if (ret == EOF)
	    break;

	if (strcmp(cmd, INSERT) == 0) {
	    scanf("%s", data);
	    hs_insert_key(h, data);
	} else if (strcmp(cmd, FIND) == 0) {
	    scanf("%s", data);
	    hs_find_key(h, data);
	} else if (strcmp(cmd, REMOVE) == 0) {
	    scanf("%s", data);
	    hs_remove_key(h, data);
	} else if (strcmp(cmd, DONE) == 0) {
	    break;
	}
    }

    hs_destroy(&h);

    return EXIT_SUCCESS;
}

