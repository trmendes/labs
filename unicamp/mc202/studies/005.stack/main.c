#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define ELEMENTS 10

int main(int argc, char **argv) {
    stack_t * s = st_create();
    for (int i = 0; i < ELEMENTS; i++) {
	node_t *element = calloc(1, sizeof(node_t));
	element->id = i+1;
	st_push(s, element);
	if (i%2==0) {
	    element = st_pop(s);
	    printf("Pop element: %d\n", element->id);
	    free(element);
	}
    }


    printf("Len of the stack: %d\n", st_len(s));
    st_print(s);
    return EXIT_SUCCESS;
}
