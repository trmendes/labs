#ifndef __BITS_H__
#define __BITS_H__

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

typedef struct bits_s {
    int32_t     nelements;
    int8_t    * bitArray;
} bits_t;

#define BIT_NBSLOTS(X) ( ( (X) / CHAR_BIT ) + 1 )
#define BIT_BSLOT(X)   ( (X) / CHAR_BIT )
#define BIT_MASK(X)    ( 1 << ( (X) % CHAR_BIT ) )

#define BIT_SET(A,X)     ( (A)[BIT_BSLOT(X)] |= BIT_MASK(X) )
#define BIT_CLEAR(A,X)   ( (A)[BIT_BSLOT(X)] &= ~BIT_MASK(X) )
#define BIT_TEST(A,X)    ( (A)[BIT_BSLOT(X)] & BIT_MASK(X) )

#define CMD_CREATE   "create"
#define CMD_ADD      "add"
#define CMD_REMOVE   "remove"
#define CMD_IN       "in"
#define CMD_RANK     "rank"
#define CMD_SELECT   "select"
#define CMD_RANGECNT "rangecount"
#define CMD_PRINT    "print"
#define CMD_EXIT     "exit"

#define ERR_OVERFLOW     -3
#define ERR_BITARR_NULL  -2
#define ERR_BITCTRL_NULL -1
#define SUCCESS           0

/* Cria um subconjunto vazio de {1,2,...,n}. Vamos chamá-lo de S. Se já
 * existe um subconjunto ele deve ser destruído e um novo subconjunto deve
 * ser criado.*/
bits_t * bt_create   (int32_t size);
/* Adiciona o elemento i a S. */
int8_t   bt_add      (bits_t * bCtrl, int32_t element);
/* Remove o elemento i de S. */
int8_t   bt_remove   (bits_t * bCtrl, int32_t element);
/* Testa se o elemento i está em S. Imprime "belongs(i) = " seguido de "true"
 * se ele estiver ou "false" se ele não estiver. */
int8_t   bt_is_in    (bits_t * bCtrl, int32_t element);
/* Imprime "rank(i) = " e o número de elementos em S que são menores ou
 * iguais a i. Se i for maior que n, o programa deve imprimir
 * "rank(i) = 0". */
int8_t   bt_rank     (bits_t * bCtrl, int32_t element);
/* Imprime "select(i) = " e o i-ésimo menor elemento em S. Se i for maior
 * que |S|, o programa deve imprimir "select(i) = 0". */
int32_t   bt_select   (bits_t * bCtrl, int32_t i);
/* Imprime "rangecount(j,k) = " e o número de elementos em S no
 * intervalo [j,k]. */
int8_t   bt_rangecnt (bits_t * bCtrl, int32_t j, int32_t k);
/* Imprime "S = " e os elementos em S em ordem crescente em uma única linha,
 * dentro de chaves e separados por vírgulas. */
int8_t   bt_print    (bits_t * bCtrl);
/* Termina o programa. */
int8_t   bt_exit     (bits_t ** bCtrl);

#endif
