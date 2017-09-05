#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

#define ELEMENTS 100

int32_t main(int32_t argc, char ** argv) {
    uint8_t v[BIT_NBSLOTS(ELEMENTS)] = {0};

    printf("Alocado um array de %d bytes\n", sizeof(v));
    printf("Modificando o valor de um BIT na posicao %d com a mascara: 0x%x\n", 1, BIT_MASK(1));

    BIT_SET(v,3);
    PRINT_BSLOT(v,0);
    BIT_SET(v,3);
    if (BIT_TEST(v,3))
	printf("Setado como 1\n");
    else
	printf("Setado como 0\n");

    return EXIT_FAILURE;
}