#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lista.h"

#define REQSIZE 7

int32_t main(int argc, char **argv) {
    list *lmtf = calloc(1, sizeof(list));
    list *ltsp = calloc(1, sizeof(list));
    list *lcnt = calloc(1, sizeof(list));
    int32_t cmtf = 0, ctsp = 0, ccnt = 0;
    int32_t req[REQSIZE] = {4, 2, 2, 4, 3, 1, 3};

    for (int i = 5; i > 0 ; i--) {
	inserir_lista(lmtf, i);
	inserir_lista(ltsp, i);
	inserir_lista(lcnt, i);
    }

    for (int i = 0; i < REQSIZE; i++) {
	cmtf += req_move_to_front(lmtf, req[i]);
	ctsp += req_transpose(ltsp, req[i]);
	ccnt += req_count(lcnt, req[i]);
    }

    printf("Custo mtf: %d\n", cmtf);
    printf("Custo tsp: %d\n", ctsp);
    printf("Custo cnt: %d\n", ccnt);

    imprimir_lista(lmtf, "lmtf");
    imprimir_lista(ltsp, "ltsp");
    imprimir_lista(lcnt, "lcnt");

    return EXIT_SUCCESS;
}
