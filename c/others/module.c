#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int32_t main(int32_t argc, char **argv) {

    int8_t size = 100;

    for (int8_t i = 0; i < size; ++i) {
	if (i%10 == 0)
	    printf("--------------\n");
	printf("%d mod %d = %d\n", i+(size*2), size, (i+(size*2))%size);
    }
    return EXIT_SUCCESS;
}