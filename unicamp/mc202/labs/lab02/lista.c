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

void imprimir_cru(list *l) {
    if (l == NULL)
	return;
    if (l->init == NULL)
	return;

    no *p = l->init;
    while (p != NULL) {
	printf("%d ", p->valor);
	p = p->prox;
    }
    printf("\n");
}

void imprimir_lista(list *l, char *name) {
    if (l == NULL)
	return;
    if (l->init == NULL)
	return;

    no *p = l->init;
    printf("\n[%s] - ", name);
    while (p != NULL) {
	printf("[A#%d|V#%d|NEXT] -> ", p->acesso, p->valor);
	p = p->prox;
    }
    printf("NULL\n");
}

void inserir_lista(list *l, int32_t dado) {
    if (l == NULL)
	return;

    no *novodado = calloc(1,sizeof(no));
    novodado->valor = dado;

    if (l->init == NULL) {
	l->init = novodado;
    } else {
	novodado->prox = l->init;
	l->init = novodado;
    }
}

int32_t req_move_to_front(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int c = 1;
    no *p = l->init;
    no *pp = l->init;

    if (p->valor == dado) {
	p->acesso++;
	return c;
    }

    while ( p != NULL) {
	if (p->valor == dado) {
	    p->acesso++;
	    pp->prox = p->prox;
	    p->prox = l->init;
	    l->init = p;
	    return c;
	}
	pp = p;
	p = p->prox;
	c++;
    }

    return 0;

}

int32_t req_transpose(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int32_t c = 1;
    no *p = l->init;
    no *pp = l->init;
    no *ppp = l->init;

    if (p->valor == dado) {
	p->acesso++;
	return c;
    }

    while (p->prox != NULL) {
	if (p->valor == dado) {
	    p->acesso++;
	    ppp->prox = p;
	    pp->prox = p->prox;
	    p->prox = pp;
	    if (ppp == pp) {
		l->init = p;
	    }
	    return c;
	}
	ppp = pp;
	pp = p;
	p = pp->prox;
	c++;
    }
    return 0;
}

int32_t req_count(list *l, int32_t dado) {
    if (l == NULL)
	return 0;
    if (l->init == NULL)
	return 0;

    int32_t c = req_move_to_front(l,dado);

    no *ppp = l->init;
    no *pp = l->init;
    no *p = l->init;

    while (p->prox != NULL) {
	p = pp->prox;
	if (pp->acesso < p->acesso) {
	    if (ppp != pp) {
		ppp->prox = p;
	    }
	    pp->prox = p->prox;
	    p->prox = pp;

	    if (l->init == pp) {
		l->init = p;
		pp = l->init;
		ppp = l->init;
		p = l->init->prox;
	    }
	} else {
	    break;
	}
	ppp = pp;
	pp = p;
    }

    return c;
}