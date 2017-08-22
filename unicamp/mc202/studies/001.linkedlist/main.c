/**
    linkedlist.cpp
    Proposito: Implementar uma lista ligada simples com algumas
    funcoes para buscar, inserir, editar, criar e remover
    - Exercicio numero 01 de MC202 - Unicamp - Ano 2017

    @author Thiago Mendes
    @version 0,1 17/08/17
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedlist.h"
#include "trace.h"

#define NCOLOR 6
#define ELEMENTS 5
#define NTODELETE 5

int main(int argc, char **argv) {
    /* variaveis para automatizar o programa */
    uint32_t r_color_index = 0;
    uint32_t r_index = 0;
    time_t t;
    node *node_tmp = NULL;
    /* Inicializa um gerador de numero randomico */
    srand((unsigned) time(&t));

    /* um array e cores para nos auxiliar */
    char *colors[NCOLOR] = {"AMARELO","PRETO", "AZUL", "MARROM", "BRANCO", "ROXO"};

    /* nossa lista ligada em l */
    linkedlist *l = ll_create();
    /* nossa copia em l2 */
    linkedlist *l2 = NULL;

    /* verificando se foi possivel alocar l */
    if (l == NULL) {
	printf("Nao foi possivel alocar espaco de memoria para a listai\n");
	return EXIT_FAILURE;
    }

    /* lista alocada e podemos inserir dados mas primeiro vamos consultar
     * quantos nos temos nessa lista */
    printf("-----------------------------------------------\n");
    printf("\t\tInserindo\n");
    printf("-----------------------------------------------\n");

    printf("# de elementos em l: %d\n",ll_len(l));

    /* Vamos inserir algumas cores em l */
    for (int i = 0; i < ELEMENTS; i++) {
	r_color_index = rand() % (NCOLOR);
	/* 3 funcoes de insert */
	switch (rand() % 3) {
	    case 0:
		ll_insert_head(l, colors[r_color_index]);
		break;
	    case 1:
		ll_insert_tail(l, colors[r_color_index]);
		break;
	    case 2:
		r_index = rand() % (ll_len(l) + 1);
		ll_insert_at_index(l, colors[r_color_index], r_index);
		break;
	}
    }

    printf("\n-----------------------------------------------\n");
    printf("\t\tEditando\n");
    printf("-----------------------------------------------\n");
    printf("# de elementos em l: %d\n",ll_len(l));

    r_index = rand() % ll_len(l);
    node_tmp = ll_get_index_node(l, r_index);
    ll_move_next_to_front(l, node_tmp);

    printf("\n-----------------------------------------------\n");
    printf("\t\tCopiando L para L2\n");
    printf("-----------------------------------------------\n");
    printf("# de elementos em l: %d\n",ll_len(l));
    l2 = ll_copylist(l);
    ll_print(l2, -1, "\nCopia da lista l\n");
    printf("-> Verificando se l2 e igual a l: ");

    if (ll_check_data(l,l2) == 0) {
	printf("[OK]\n");
    } else {
	printf("[NOK]\n");
    }

    printf("-> Modificando a ordem de um elemento de L2\n");
    r_index = rand() % ll_len(l);
    node_tmp = ll_get_index_node(l, r_index);
    ll_move_next_to_front(l2, node_tmp);

    printf("-> Verificando se l2 ainda tem os mesmos elementos: ");
    if (ll_check_data(l,l2) == 0) {
	printf("[OK]\n");
    } else {
	printf("[NOK]\n");
    }

    printf("\n-----------------------------------------------\n");
    printf("\t\tRemovendo L\n");
    printf("-----------------------------------------------\n");
    printf("# de elementos em l: %d\n",ll_len(l));

    for (int i = 0; i < NTODELETE ; i++) {
	/* 8 funcoes de remove rand() % 7 */
	//switch (rand() % 8) {
	switch (7) {
	    case 0:
		ll_remove_head(l);
		break;
	    case 1:
		ll_remove_tail(l);
		break;
	    case 2:
		ll_remove_tail_but_one(l);
		break;
	    case 3:
		r_index = rand() % (ll_len(l) + 1);
		node_tmp = ll_get_index_node(l, r_index);
		ll_remove_specific_node(l,node_tmp);
		break;
	    case 4:
		r_index = rand() % (ll_len(l) + 1);
		ll_remove_specific_index(l, r_index);
		break;
	    case 5:
		r_color_index = rand() % (NCOLOR);
		ll_remove_specific_color(l,colors[r_color_index]);
		break;
	    case 6:
		r_color_index = rand() % (NCOLOR);
		ll_remove_all_color(l, colors[r_color_index]);
		break;
	    case 7:
		ll_remove_min_id(l);
		break;
	}
    }

    /* ja que chegamos ao final do main vamos destruir a lista */
    ll_destroy(&l);
    return EXIT_SUCCESS;
}
