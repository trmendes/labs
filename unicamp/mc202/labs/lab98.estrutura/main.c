#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

#define INSERT_PUSH 1
#define REMOVE_POP  2

int main(int argc, char **argv) {

    int cmdCounter = 1, command, data, i = 0;
    stack_t *stack = NULL;
    queue_t *queue = NULL;
    int isQueue = 1, isStack = 1, ret;

    while (cmdCounter > 0) {
	scanf("%d", &cmdCounter);
	if (cmdCounter == 0)
	    break;

	stack = st_create();
	queue = qe_create();

	for (i = 0; i < cmdCounter; i++) {
	    scanf("%d %d", &command, &data);
	    if (command == INSERT_PUSH) {
		st_push(stack, data);
		qe_insert(queue, data);
	    } else if (command == REMOVE_POP) {
		ret = st_pop(stack);
		if (ret != data)
		    isStack = 0;
		ret = qe_get(queue);
		if (ret != data)
		    isQueue = 0;
	    }
	}

	st_destroy(stack);
	qe_destroy(queue);

	if ((isStack) && (!isQueue))
	    printf("pilha\n");
	if ((isQueue) && (!isStack))
	    printf("fila\n");
	if ((isStack) && (isQueue))
	    printf("duvida\n");
	if ((!isStack) && (!isQueue))
	    printf("impossivel\n");

	isStack = 1;
	isQueue = 1;
    }

    return EXIT_SUCCESS;
}
