#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"

#define INPUTSIZE 100

int32_t main(int32_t argc, char ** argv) {
    char cmd[INPUTSIZE];
    int32_t argc1, argc2;
    bits_t * bCtrl = NULL;

    while (1) {
	scanf("%s", cmd);
	if (strcmp(cmd, CMD_CREATE) == 0) {
	    scanf("%d", &argc1);
	    bCtrl = bt_create(argc1);
	} else if (strcmp(cmd, CMD_ADD) == 0) {
	    scanf("%d", &argc1);
	    bt_add(bCtrl, argc1);
	} else if (strcmp(cmd, CMD_REMOVE) == 0) {
	    scanf("%d", &argc1);
	    bt_remove(bCtrl, argc1);
	} else if (strcmp(cmd, CMD_IN) == 0) {
	    scanf("%d", &argc1);
	    bt_is_in(bCtrl, argc1);
	} else if (strcmp(cmd, CMD_RANK) == 0) {
	    scanf("%d", &argc1);
	    bt_rank(bCtrl, argc1);
	} else if (strcmp(cmd, CMD_SELECT) == 0) {
	    scanf("%d", &argc1);
	    bt_select(bCtrl, argc1);
	} else if (strcmp(cmd, CMD_RANGECNT) == 0) {
	    scanf("%d %d", &argc1, &argc2);
	    bt_rangecnt(bCtrl, argc1, argc2);
	} else if (strcmp(cmd, CMD_PRINT) == 0) {
	    bt_print(bCtrl);
	} else if (strcmp(cmd, CMD_EXIT) == 0) {
	    bt_exit(&bCtrl);
	    break;
	}
    }
    return EXIT_SUCCESS;
}