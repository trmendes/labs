#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lista.h"

#define REQSIZE 10000

int32_t main() {
    list *lmtf = calloc(1, sizeof(list));
    list *ltsp = calloc(1, sizeof(list));
    list *lcnt = calloc(1, sizeof(list));

    int32_t cmtf = 0, ctsp = 0, ccnt = 0;
    int32_t n, r, req;

    scanf("%d", &n);
    scanf("%d", &r);

    for (int i = n; i > 0 ; --i) {
	inserir_lista(lmtf, i);
	inserir_lista(ltsp, i);
	inserir_lista(lcnt, i);
    }


    for (int i = 0; i < r; ++i) {
	scanf("%d ", &req);
	cmtf += req_move_to_front(lmtf, req);
	ctsp += req_transpose(ltsp, req);
	ccnt += req_count(lcnt, req);
    }

    printf("%d %d %d\n", cmtf, ctsp, ccnt);

    return EXIT_SUCCESS;
}
