#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdint.h>

typedef struct sno {
    int32_t     acesso;
    int32_t     valor;
    struct sno *prox;
} no;

typedef struct slist {
    no * init;
} list;

void    imprimir_list      (list *l);
void    inserir_lista      (list *l, int32_t dado);
int32_t req_move_to_front  (list *l, int32_t dado);
int32_t req_transpose      (list *l, int32_t dado);
int32_t req_count          (list *l, int32_t dado);

#endif