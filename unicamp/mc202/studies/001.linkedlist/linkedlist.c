#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedlist.h"
#include "trace.h"

linkedlist * ll_create() {
   linkedlist *l = (linkedlist *) calloc(1, sizeof(linkedlist));
   return l;
}

int8_t ll_destroy(linkedlist **l) {

    if (*l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    node *p = NULL;

    while ((*l)->head != (node *) NULL) {
	p = (*l)->head;
	(*l)->head = (*l)->head->next;
	(*l)->length--;
	free(p->cor);
	free(p);
    }

    (*l)->head = (node *) NULL;
    l = (linkedlist **) NULL;

    return SUCCESS;
}

void ll_print(linkedlist *l, int8_t color_index, char *extra) {
    if (l == (linkedlist *) NULL) {
	return;
    }

    int8_t index = 0;
    node *p = l->head;

    if (extra != (char *) NULL)
	printf("%s%s%s ", ANSI_COLOR_YELLOW, extra, ANSI_COLOR_RESET);

    printf("%s[LIST|FIRST]%s %s->%s ", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, ANSI_COLOR_RED, ANSI_COLOR_RESET);
    while (p != (node *) NULL) {
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

int8_t ll_insert_head(linkedlist *l, char *color) {

    if (l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    node *p = (node *) calloc(1, sizeof(node));
    p->id = l->tail_id++;
    p->cor = (char *) calloc(1,strlen(color));
    strcpy(p->cor, color);

    if (l->head == (node *) NULL) {
	l->head = p;
    } else {
	p->next = l->head;
	l->head = p;
    }

    l->length++;

    return SUCCESS;
}

int8_t ll_insert_tail(linkedlist *l, char *color) {
    if (l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    node *p = (node *) NULL;
    node *np = (node *) calloc(1,sizeof(node));
    np->id = l->tail_id++;
    np->cor = (char *) calloc(1,strlen(color));
    strcpy(np->cor, color);
    np->next = (node *) NULL;

    if (l->head == (node *) NULL) {
	l->head = np;
    } else {
	p = l->head;
	while (p->next != (node *) NULL) {
	    p = p->next;
	}
	p->next = np;

    }

    l->length++;

    return SUCCESS;
}

int8_t ll_insert_at_index(linkedlist *l, char *color, uint32_t index) {
    if (l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    uint32_t i = 0;
    node *p = NULL, *pp = NULL;

    node *np = (node *) calloc(1, sizeof(node));
    np->id = l->tail_id++;
    np->cor = (char *) calloc(1,strlen(color));
    strcpy(np->cor, color);

    /* Caso o index passado seja maior que a quantidade de elementos na lista
     * o elemento sera inserido no final da lista */
    if (index > l->length-1) {
	index = l->length-1;
    }

    if (l->head == (node *) NULL) {
	l->head = np;
    } else {
	p = l->head;
	pp = l->head;
	while (p != (node *) NULL) {
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

    return SUCCESS;
}

int8_t ll_remove_head(linkedlist *l) {
    if (l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    node *p = l->head;
    l->head = p->next;

    l->length--;

    free(p->cor);
    free(p);

    return SUCCESS;
}

int8_t ll_remove_tail(linkedlist *l) {
    if (l == (linkedlist *) NULL) {
	return ERR_NULL_LIST;
    }

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    node *p = l->head;
    node *pp = (node *) NULL;

    while (p->next != (node *) NULL) {
	pp = p;
	p = pp->next;
    }

    if (p == l->head) {
	l->head = (node *) NULL;
    } else {
	pp->next = (node *) NULL;
    }

    l->length--;

    free(p->cor);
    free(p);

    return SUCCESS;
}

int8_t ll_remove_tail_but_one(linkedlist *l) {
   if (l == (linkedlist *) NULL) {
       return ERR_NULL_LIST;
   }

   /* nenhum ou um elemento */
   if ((l->head == (node *) NULL) || (l->head->next == (node *) NULL)) {
       return ERR_NEED_MORE_EL;
   }

   node *pp = l->head;
   node *p = l->head;
   uint32_t i = 0;

   while (p->next->next != (node *) NULL) {
       pp = p;
       p = p->next;
       i++;
   }

   if (pp == p) {
       /* uma lista com somente dois elementos */
       l->head = p->next;
   } else {
       /* uma lista com mais de dois elementos */
       pp->next = p->next;
   }

   l->length--;

   free(p->cor);
   free(p);

   return SUCCESS;
}

int8_t ll_remove_specific_node(linkedlist *l, node *_p) {
    if (_p == (node *) NULL)
	return ERR_NULL_ARG;

    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    /* nenhum elemento na lista */
    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    uint32_t i = 0;
    node *p = l->head;
    node *pp = l->head;

    while (p != (node *) NULL) {
	if (p->id == _p->id) {

	    if (p == pp) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    free(p->cor);
	    free(p);
	    return SUCCESS;
	}
	pp = p;
	p = p ->next;
	i++;
    }

    return CANT_FIND_NODE;
}

int8_t ll_remove_specific_index(linkedlist *l, uint32_t index) {
    if (l->length < index)
	return ERR_WRONG_RANGE;

    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    uint32_t i = 0;
    node *p = l->head;
    node *pp = l->head;

    while (p != (node *) NULL) {
	if (i == index) {
	    if (pp == p) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    free(p->cor);
	    free(p);

	    return SUCCESS;
	}
	pp = p;
	p = p->next;
	i++;
    }

    return CANT_FIND_NODE;
}

int8_t ll_remove_specific_color(linkedlist *l, char *color) {
    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (color == (char *) NULL)
	return ERR_NULL_ARG;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    node *p = l->head;
    node *pp = l->head;
    uint32_t i = 0;

    while (p != (node *) NULL) {
	if (strcmp(p->cor,color) == 0) {
	    if (p == pp) {
		l->head = p->next;
	    } else {
		pp->next = p->next;
	    }

	    l->length--;

	    free(p->cor);
	    free(p);

	    return SUCCESS;
	}
	pp = p;
	p = p->next;
	i++;
    }
    return CANT_FIND_NODE;
}

/* Questao 8 do PDF 1 */
int8_t ll_remove_all_color(linkedlist *l, char *color) {
    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (color == (char *) NULL)
	return ERR_NULL_ARG;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    uint32_t i = 0;
    node *p = l->head;
    node *pp = l->head;
    node *p_to_rem = l->head;

    while (p != (node *) NULL) {
	if (strcmp(p->cor,color) == 0) {
	    p_to_rem = p;

	    if (p == pp) {
		l->head = p->next;
		p = l->head;
		pp = l->head;
	    } else {
		pp->next = p->next;
		p = p->next;
	    }

	    l->length--;

	    free(p_to_rem->cor);
	    free(p_to_rem);
	    --i;

	} else {
	    pp = p;
	    p = p->next;
	}
	++i;
    }

    return SUCCESS;
}

node* ll_get_index_node(linkedlist *l, uint32_t index) {
    if (l == (linkedlist *) NULL)
	return NULL;

    if ((l->head == (node *) NULL) || (l->length < index))
	return NULL;

    uint32_t i = 0;
    node *p = l->head;

    while (p != (node *) NULL) {
	if (i==index)
	    return p;
	++i;
	p = p->next;
    }

    return (node *) NULL;
}

uint32_t ll_get_index_head_specific_node(linkedlist *l, node *_p) {
    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (_p == (node *) NULL)
	return ERR_NULL_ARG;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    uint32_t i = 0;
    node *p = l->head;

    while (p != (node *) NULL) {
	if (p->id == _p->id)
	    return i;
	++i;
	p = p->next;
    }

    return SUCCESS;
}

uint32_t ll_len(linkedlist *l) {
    if (l == (linkedlist *) NULL) {
        return ERR_NULL_LIST;
    }

    return l->length;
}

/* Questao 9 do PDF 1 */
int8_t ll_move_next_to_front (linkedlist *l, node *_p) {
    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (_p == (node *) NULL)
	return ERR_NULL_ARG;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    node *p = l->head;
    node *pn = (node *) NULL;
    uint32_t i = 1;

    while (p->next != (node *) NULL) {
	if (p->id == _p->id) {
	    pn = p->next;
	    p->next = pn->next;
	    pn->next = l->head;
	    l->head = pn;
	    break;
	}
	p = p->next;
	++i;
    }
    return 0;
}

/* Questao 10 do PDF 1 */
int8_t ll_remove_min_id(linkedlist *l) {
    if (l == (linkedlist *) NULL)
	return ERR_NULL_LIST;

    if (l->head == (node *) NULL)
	return ERR_EMPT_LIST;

    node *p = l->head;
    node *pp = l->head;
    node *ppmin = l->head;
    node *pmin = l->head;
    uint32_t i = 0;

    while (p != (node *) NULL) {
	if (pmin->id > p->id) {
	    ppmin = pp;
	    pmin = p;
	}
	pp = p;
	p = p->next;
	++i;
    }

    if (l->head == pmin) {
	l->head = pmin->next;
    }
    ppmin->next = pmin->next;
    free(pmin->cor);
    free(pmin);

    return SUCCESS;
}

/* Questao 11 do PDF 1 */
linkedlist * ll_copylist(linkedlist *l) {
    linkedlist *l2 = ll_create();

    if (l2 == (linkedlist *) NULL) {
	printf("Nao foi possivel alocar memoria para a copia da lista\n");
	return (linkedlist *) NULL;
    }

    l2->length = l->length;
    l2->tail_id = l->tail_id;

    if (l->head != (node *) NULL) {
	node * p = l->head;
	while (p != (node *) NULL) {
	    node * nn = (node *) calloc(1, sizeof(node));
	    nn->id = p->id;
	    nn->cor = (char *) calloc(1, sizeof(p->cor));
	    strcpy(nn->cor, p->cor);
	    ll_insert_tail_copy(l2,nn);
	    p = p->next;
	}
    }

    return l2;
}

int8_t ll_insert_tail_copy(linkedlist *l, node *np) {
    if (l == (linkedlist *) NULL) {
	return ERR_EMPT_LIST;
    }

    if (np == (node *) NULL)
	return ERR_NULL_ARG;

    node *p = (node *) NULL;

    if (l->head == (node *) NULL) {
	l->head = np;
    } else {
	p = l->head;
	while (p->next != (node *) NULL) {
	    p = p->next;
	}
	p->next = np;
    }

    return SUCCESS;
}

/* Questao 12 do PDF 1 */
int8_t ll_check_data(linkedlist *l1, linkedlist *l2) {
    if ((l1 == (linkedlist *) NULL) || (l2 == (linkedlist *) NULL))
	return ERR_NULL_LIST;
    if ((l1->head == (node *) NULL) || (l2->head == (node *) NULL))
	return ERR_EMPT_LIST;

    uint8_t found = 0;
    node *p1 = l1->head;
    node *p2 = (node *) NULL;

    while (p1 != (node *) NULL) {
	p2 = l2->head;
	while (p2 != (node *) NULL) {
	    if ((p1->id == p2->id) && (strcmp(p1->cor, p2->cor) == 0)) {
		found = 1;
		break;
	    }
	    p2 = p2->next;
	}
	if (found == 0) {
	    return CANT_FIND_NODE;
	}
	found = 0;
	p1 = p1->next;
    }
    return SUCCESS;
}

/* Questao 13 do PDF 1 */
/* Questao 14 do PDF 1 */
/* Questao 15 do PDF 1 */
/* Questao 16 do PDF 1 */
