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

/**
    Verifica o ponteiro da estrutura de controle da lista ligada

    @param *l endereco da estrutura de controle da lista ligada
    @returns  -1 caso a lista nao esteja inicializada
               0 caso a lista esteja ok
*/
int8_t check_list(linkedlist *l) {
    if (l == NULL) {
	printf("Acho que voce esqueceu de inicializar a lista chamando o ll_create!i\n");
	return -1;
    }
    return 0;
}

/**
    Cria e inicializa uma estrutura que gerencia a lista ligada

    @return uma estrutura de gerenciamento da lista ligada implementada
    neste exercício
*/
linkedlist * ll_create() {
   linkedlist *l = calloc(1, sizeof(linkedlist));
   return l;
}

/**
    Percorre todos os nos de uma lista para desalocar a memoria alocada
    para cada no

    @params **l endereco da estrutura que gerencia a lista ligada
    @return -1 caso nao seja possivel acessar o controle da lista
             0 caso a opercao de limpeza tenha sucesso
*/
int8_t ll_destroy(linkedlist **l) {

    if (check_list(*l) == -1) {
	return -1;
    }

    node *p = NULL;


    while ((*l)->head != NULL) {
	p = (*l)->head;
	ll_print(*l,0 , "\nAntes :");
	(*l)->head = (*l)->head->next;
	(*l)->length--;
	printf("-> Removendo o elemento [LS%d] - #ID %d | COR %s\n\n", (*l)->length, p->id, p->cor);
	ll_print(*l,-1, "Depois:");
	free(p->cor);
	free(p);
    }

    (*l)->head = NULL;
    l = NULL;

    return 0;
}

/**
    Imprime todos os elementos da lista ligada

    @param *l ponteiro para a estrutura da lista ligada
    @param color_index <0  caso nao queira colorir nenhum index da lista
                       >=0 posicao que deseja colorir
*/
void ll_print(linkedlist *l, int8_t color_index, char *extra) {
    if (check_list(l) == -1) {
	return;
    }

    int8_t index = 0;
    node *p = l->head;

    if (extra != NULL)
	printf("%s%s%s ", ANSI_COLOR_YELLOW, extra, ANSI_COLOR_RESET);

    printf("%s[LIST|FIRST]%s %s->%s ", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, ANSI_COLOR_RED, ANSI_COLOR_RESET);
    while (p != NULL) {
	if (color_index == index) {
	    printf("%s[%d|%s|NEXT]%s %s->%s ",ANSI_COLOR_RED, p->id, p->cor, ANSI_COLOR_RESET, ANSI_COLOR_RED, ANSI_COLOR_RESET);
	} else {
	    printf("%s[%d|%s|NEXT]%s %s->%s ", ANSI_COLOR_GREEN, p->id, p->cor, ANSI_COLOR_RESET,  ANSI_COLOR_RED, ANSI_COLOR_RESET);
	}
	p = p->next;
	index++;
    }
    printf("%sNULL%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
}

/**
    Insere uma cor no primeio no de uma lista ligada

    @param *l     ponteiro para a estrutura da lista ligada
    @param *color string da cor que sera inserida na lista
    @return -1 se nao conseguiu ter acesso a lista
             0 se a cor foi inserida na lista
             1 se a cor nao foi inserida na lista
*/
int8_t ll_insert_head(linkedlist *l, char *color) {

    if (check_list(l) == -1) {
	return -1;
    }

    ll_print(l,-1, "\nAntes :");

    node *p = calloc(1, sizeof(node));
    p->id = l->tail_id++;
    p->cor = calloc(1,strlen(color));
    strcpy(p->cor, color);
    /* Esse passo nao e necessario pois a estrutura ja foi inicializada
     * com zero pelo calloc */
    p->next = NULL;

    if (l->head == NULL) {
	l->head = p;
    } else {
	p->next = l->head;
	l->head = p;
    }

    l->length++;

    printf("-> Inserindo elemento no começo da lista: [LS%d] - #ID %d | COR %s\n", l->length, p->id, p->cor);
    ll_print(l, 0, "Depois:");

    return 0;
}

/**
    Insere o novo no de cor no fim da lista

    @param *l     ponteiro para a estrutura da lista ligada
    @param *color string da cor que sera inserida na lista
    @return -1 se nao conseguiu ter acesso a lista
             0 se a cor foi inserida na lista
             1 se a cor nao foi inserida na lista
*/
int8_t ll_insert_tail(linkedlist *l, char *color) {
    if (check_list(l) == -1) {
	return -1;
    }

    ll_print(l,-1, "\nAntes :");

    node *p = NULL;
    node *np = calloc(1,sizeof(node));
    np->id = l->tail_id++;
    np->cor = calloc(1,strlen(color));
    strcpy(np->cor, color);
    np->next = NULL;

    if (l->head == NULL) {
	l->head = np;
    } else {
	p = l->head;
	while (p->next != NULL) {
	    p = p->next;
	}
	p->next = np;

    }

    l->length++;

    printf("-> Inserindo elemento no fim da lista: [LS%d] - #ID %d | COR %s\n", l->length, np->id, np->cor);
    ll_print(l, l->length-1, "Depois:");

    return 0;
}

/**
    Insere o novo no index desejado. Caso o index nao exista sera inserido
    no final da lista

    @param *l     ponteiro para a estrutura da lista ligada
    @param *color string da cor que sera inserida na lista
    @param index  index onde deseja inserir o no. se o index seja maior que
                  o tamanho da fila, o no sera inserido no final da fila
    @return -1 se nao conseguiu ter acesso a lista
             0 se a cor foi inserida na lista
             1 se a cor nao foi inserida na lista
*/
int8_t ll_insert_at_index(linkedlist *l, char *color, uint32_t index) {
    if (check_list(l) == -1) {
	return -1;
    }

    uint32_t i = 0;
    node *p = NULL, *pp = NULL;

    ll_print(l,-1, "\nAntes :");

    node *np = calloc(1, sizeof(node));
    np->id = l->tail_id++;
    np->cor = calloc(1,strlen(color));
    strcpy(np->cor, color);
    np->next = NULL;

    /* Caso o index passado seja maior que a quantidade de elementos na lista
     * o elemento sera inserido no final da lista */
    if (index > l->length-1) {
	index = l->length-1;
    }

    if (l->head == NULL) {
	l->head = np;
    } else {
	p = l->head;
	pp = l->head;
	while (p != NULL) {
	    if (index == i) {
		if (p == pp) {
		    np->next = p;
		    l->head = np;
		    break;
		} else {
		    pp->next = np;
		    np->next = p;
		    break;
		}
	    }
	    pp = p;
	    p = p->next;
	    i++;
	}
    }

    l->length++;

    printf("-> Inserindo elemento no indice %d da lista: [LS%d] - #ID %d | COR %s\n", index, l->length, np->id, np->cor);
    ll_print(l, index, "Depois:");

    return 0;
}

int8_t ll_remove_head(linkedlist *l) {
    if (check_list(l) == -1) {
	return -1;
    }

    if (l->head == NULL)
	return -1;

    ll_print(l, 0, "\nAntes :");

    node *p = l->head;
    l->head = p->next;

    l->length--;

    printf("-> Removendo o elemento do inicio da lista: [LS%d] - #ID %d | COR %s\n", l->length, p->id, p->cor);
    ll_print(l, -1, "Depois:");

    free(p->cor);
    free(p);

    return 0;
}

int8_t ll_remove_tail(linkedlist *l) {
    if (check_list(l) == -1) {
	return -1;
    }

    if (l->head == NULL)
	return -1;

    ll_print(l,l->length-1, "\nAntes :");

    node *p = l->head;
    node *pp = NULL;

    while (p->next != NULL) {
	pp = p;
	p = pp->next;
    }

    if (p == l->head) {
	l->head = NULL;
    } else {
	pp->next = NULL;
    }

    l->length--;

    printf("-> Removendo o elemento do fim da lista: [LS%d] - #ID %d | COR %s\n", l->length, p->id, p->cor);
    ll_print(l, -1, "Depois:");

    free(p->cor);
    free(p);

    return 0;
}

int8_t ll_remove_tail_but_one(linkedlist *l) {
   if (check_list(l) == -1) {
       return -1;
   }

   /* nenhum ou um elemento */
   if ((l->head == NULL) || (l->head->next == NULL)) {
       return -1;
   }


   node *pp = l->head;
   node *p = l->head;
   uint32_t i = 0;

   while (p->next->next != NULL) {
       pp = p;
       p = p->next;
       i++;
   }

    ll_print(l, i, "\nAntes :");

   if (pp == p) {
       /* uma lista com somente dois elementos */
       l->head = p->next;
   } else {
       /* uma lista com mais de dois elementos */
       pp->next = p->next;
   }

   l->length--;

   printf("-> Removendo o penultimo elemento da lista: [LS%d] - #ID %d | COR %s\n", l->length, p->id, p->cor);
   ll_print(l, -1, "Depois:");

   free(p->cor);
   free(p);

   return 0;
}

int8_t ll_remove_specific_node(linkedlist *l, node *_p) {
    if (_p == NULL)
	return -1;

    if (check_list(l) == -1)
	return -1;

    /* nenhum elemento na lista */
    if (l->head == NULL)
	return -1;

    uint32_t i = 0;
    node *p = l->head;
    node *pp = l->head;

    while (p != NULL) {
	if (p->id == _p->id) {
	    ll_print(l, i, "\nAntes :");

	    if (p == pp) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    printf("-> Removendo um no especifico da lista: [LS%d] - #ID %d | COR %s\n", l->length, p->id, p->cor);
	    ll_print(l, -1, "Depois:");

	    free(p->cor);
	    free(p);
	    return 1;
	}
	pp = p;
	p = p ->next;
	i++;
    }

    return 0;
}

int8_t ll_remove_specific_index(linkedlist *l, uint32_t index) {
    if (l->length < index)
	return -1;

    if (l->head == NULL)
	return -1;

    uint32_t i = 0;
    node *p = l->head;
    node *pp = l->head;

    while (p != NULL) {
	if (i == index) {
	    ll_print(l, index, "\nAntes :");
	    if (pp == p) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    printf("-> Removendo um no da lista no indice %d: [LS%d] - #ID %d | COR %s\n", index, l->length, p->id, p->cor);
	    ll_print(l, -1, "Depois:");

	    free(p->cor);
	    free(p);
	    return 1;
	}
	pp = p;
	p = p->next;
	i++;
    }

    return 0;
}

int8_t ll_remove_specific_color(linkedlist *l, char *color) {
    if (check_list(l) == -1)
	return -1;

    if (color == NULL)
	return -1;

    if (l->head == NULL)
	return -1;

    node *p = l->head;
    node *pp = l->head;
    uint32_t i = 0;

    while (p != NULL) {
	if (strcmp(p->cor,color) == 0) {
	    ll_print(l, i, "\nAntes :");

	    if (p == pp) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    printf("-> Removendo o primeiro no da lista de cor %s: [LS%d] - #ID %d | COR %s\n", color, l->length, p->id, p->cor);
	    ll_print(l, -1, "Depois:");

	    free(p->cor);
	    free(p);
	    return 1;
	}
	pp = p;
	p = p->next;
	i++;
    }
    return 0;
}

/* Questao 8 do PDF 1 */
int8_t ll_remove_all_color(linkedlist *l, char *color) {
    if (check_list(l) == -1)
	return -1;

    if (color == NULL)
	return -1;

    if (l->head == NULL)
	return -1;

    uint32_t i = 0, j = 0;
    node *p = l->head;
    node *pp = l->head;
    node *prem = l->head;

    while (p != NULL) {
	if (strcmp(p->cor,color) == 0) {
	    ll_print(l, i, "\nAntes :");
	    prem = p;

	    if (p == pp) {
		l->head = p->next;
		p = l->head;
		pp = l->head;
	    } else {
		pp->next = p->next;
		p = p->next;
	    }

	    l->length--;

	    printf("-> Removendo da lista a cor %s: [#%d] [LS%d] - #ID %d | COR %s\n", color, j++, l->length, prem->id, prem->cor);
	    ll_print(l, -1, "Depois:");

	    free(prem->cor);
	    free(prem);
	    i--;
	} else {
	    pp = p;
	    p = p->next;
	}
	i++;
    }

    return 0;
}

node* ll_get_index_node(linkedlist *l, uint32_t index) {
    if (check_list(l) == -1)
	return NULL;

    if ((l->head == NULL) || (l->length < index))
	return NULL;

    uint32_t i = 0;
    node *p = l->head;

    while (p != NULL) {
	if (i==index)
	    return p;
	i++;
	p = p->next;
    }

    return NULL;
}

uint32_t ll_get_index_head_specific_node(linkedlist *l, node *_p) {
    if (check_list(l) == -1)
	return -1;

    if (l->head == NULL)
	return -1;

    uint32_t i = 0;
    node *p = l->head;

    while (p != NULL) {
	if (p->id == _p->id)
	    return i;
	i++;
	p = p->next;
    }
    return 0;
}

/**
    Retorna o tamanho da lista ligada controlada pela estrutura de lista

    @param *l ponteiro para a estrutura da lista ligada
    @return -1 se nao conseguiu ter acesso a lista 
            =>0 quantidade de elementos inseridos na lista ligada
*/
uint32_t ll_len(linkedlist *l) {
    if (check_list(l) == -1) {
        return -1;
    }

    return l->length;
}

/* Questao 9 do PDF 1 */
int8_t ll_move_next_to_front (linkedlist *l, node *_p) {
    if (check_list(l) == -1)
	return -1;

    if (_p == NULL)
	return -1;

    if (l == NULL)
	return -1;

    if (l->head == NULL)
	return -1;

    node *p = l->head;
    node *pn = NULL;
    uint32_t i = 1;

    while (p->next != NULL) {
	if (p->id == _p->id) {
	    ll_print(l, i, "Antes :");
	    pn = p->next;
	    p->next = pn->next;
	    pn->next = l->head;
	    l->head = pn;
	    printf("-> Movendo o elemento apontado por [%d|%s|NEXT] para o inicio da lista\n", _p->id, _p->cor);
	    ll_print(l, 0, "Depois:");
	    break;
	}
	p = p->next;
	i++;
    }
    return 0;
}

/* Questao 10 do PDF 1 */
int8_t ll_remove_min_id(linkedlist *l) {
    if (check_list(l) == -1)
	return -1;
    if (l->head == NULL)
	return -1;

    node *p = l->head;
    node *pp = l->head;
    node *ppmin = l->head;
    node *pmin = l->head;
    uint32_t i = 0, imin = 0;

    while (p != NULL) {
	if (pmin->id > p->id) {
	    ppmin = pp;
	    pmin = p;
	    imin = i;
	}
	pp = p;
	p = p->next;
	i++;
    }

    ll_print(l, imin, "\nAntes :");
    printf("-> Removendo no com valor de ID menor [%d|%s|NEXT]\n", pmin->id, pmin->cor);
    if (l->head == pmin) {
	l->head = pmin->next;
    }
    ppmin->next = pmin->next;
    free(pmin->cor);
    free(pmin);
    ll_print(l, -1, "Depois:");

    return 0;
}

/* Questao 11 do PDF 1 */
linkedlist * ll_copylist(linkedlist *l) {
    linkedlist *l2 = ll_create();

    if (l2 == NULL)
	printf("Nao foi possivel alocar memoria para a copia da lista\n");

    l2->length = l->length;
    l2->tail_id = l->tail_id;

    if (l->head != NULL) {
	node * p = l->head;
	while (p != NULL) {
	    node * nn = calloc(1, sizeof(node));
	    nn->id = p->id;
	    nn->cor = calloc(1, sizeof(p->cor));
	    strcpy(nn->cor, p->cor);
	    ll_insert_tail_copy(l2,nn);
	    p = p->next;
	}
    }

    return l2;
}

int8_t ll_insert_tail_copy(linkedlist *l, node *np) {
    if (check_list(l) == -1) {
	return -1;
    }

    if (np == NULL)
	return -1;

    node *p;

    if (l->head == NULL) {
	l->head = np;
    } else {
	p = l->head;
	while (p->next != NULL) {
	    p = p->next;
	}
	p->next = np;
    }

    return 0;
}

/* Questao 12 do PDF 1 */
int8_t ll_check_data(linkedlist *l1, linkedlist *l2) {
    if ((l1 == NULL) || (l2 == NULL))
	return -1;
    if ((l1->head == NULL) || (l2->head == NULL))
	return -1;

    uint8_t found = 0;
    node *p1 = l1->head;
    node *p2 = NULL;

    while (p1 != NULL) {
	p2 = l2->head;
	while (p2 != NULL) {
	    if ((p1->id == p2->id) && (strcmp(p1->cor, p2->cor) == 0)) {
		found = 1;
		break;
	    }
	    p2 = p2->next;
	}
	if (found == 0) {
	    return -1;
	}
	found = 0;
	p1 = p1->next;
    }
    return 0;
}

/* Questao 13 do PDF 1 */
/* Questao 14 do PDF 1 */
/* Questao 15 do PDF 1 */
/* Questao 16 do PDF 1 */
