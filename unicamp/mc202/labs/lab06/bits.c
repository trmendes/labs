#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

/* Cria um subconjunto vazio de {1,2,...,n}. Vamos chamá-lo de S. Se já
 * existe um subconjunto ele deve ser destruído e um novo subconjunto deve
 * ser criado.*/
bits_t * bt_create(int32_t size) {
    bits_t * bitCtrl = calloc(1, sizeof(bits_t));
    bitCtrl->nelements = size;
    bitCtrl->bitArray = calloc(BIT_NBSLOTS(size), sizeof(int8_t));
    return bitCtrl;
}
/* Adiciona o elemento i a S. */
int8_t bt_add(bits_t * bCtrl, int32_t element) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    if (element > bCtrl->nelements)
	return ERR_OVERFLOW;

    BIT_SET(bCtrl->bitArray, element);

    return SUCCESS;
}

/* Remove o elemento i de S. */
int8_t bt_remove(bits_t * bCtrl, int32_t element) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    if (element > bCtrl->nelements)
	return ERR_OVERFLOW;

    BIT_CLEAR(bCtrl->bitArray, element);

    return SUCCESS;
}

/* Testa se o elemento i está em S. Imprime "belongs(i) = " seguido de "true"
 * se ele estiver ou "false" se ele não estiver. */
int8_t bt_is_in(bits_t * bCtrl, int32_t element) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    if (element > bCtrl->nelements)
	return ERR_OVERFLOW;

    printf("belongs(%d) = ", element);
    if (BIT_TEST(bCtrl->bitArray, element))
	printf("true\n");
    else
	printf("false\n");

    return SUCCESS;
}

/* Imprime "rank(i) = " e o número de elementos em S que são menores ou
 * iguais a i. Se i for maior que n, o programa deve imprimir
 * "rank(i) = 0". */
int8_t bt_rank(bits_t * bCtrl, int32_t element) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    int32_t count = 0, i;

    if (element < bCtrl->nelements) {
	for (i = element; i != 0; i--) {
	    if (BIT_TEST(bCtrl->bitArray, i))
		count++;
	}
    }

    printf("rank(%d) = %d\n", element, count);

    return SUCCESS;
}

/* Imprime "select(i) = " e o i-ésimo menor elemento em S. Se i for maior
 * que |S|, o programa deve imprimir "select(i) = 0". */
int32_t bt_select(bits_t * bCtrl, int32_t i) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    int32_t ret = 0;
    int32_t cnt = 0;
    int32_t iTmp = i;

    if (bCtrl->nelements > i) {
	for ( i = 0; i < bCtrl->nelements ; i++) {
	    if (BIT_TEST(bCtrl->bitArray, i)) {
		cnt++;
		if (cnt == iTmp) {
		    ret = i;
		    break;
		}
	    }
	}
    }

    printf("select(%d): %d\n", iTmp, ret);

    return SUCCESS;
}

/* Imprime "rangecount(j,k) = " e o número de elementos em S no
 * intervalo [j,k]. */
int8_t bt_rangecnt(bits_t * bCtrl, int32_t j, int32_t k) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    int32_t count = 0, i;

    if ((j > 0) && (k < bCtrl->nelements)) {
	for (i = j; i != k; i++) {
	    if (BIT_TEST(bCtrl->bitArray, i))
		count++;
	}
	printf("rangecount(%d,%d) = %d\n", j, k, count);
    }

    return SUCCESS;
}

/* Imprime "S = " e os elementos em S em ordem crescente em uma única linha,
 * dentro de chaves e separados por vírgulas. */
int8_t bt_print(bits_t * bCtrl) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;
    if (bCtrl->bitArray == NULL)
	return ERR_BITCTRL_NULL;

    int32_t i, back = 0;

    printf("S = {");
    for (i = 0; i < bCtrl->nelements; i++) {
	if (BIT_TEST(bCtrl->bitArray, i)) {
	    printf("%d,", i);
	    back = 1;
	}
    }

    if (back == 1)
	printf("\b");

    printf("}\n");

    return SUCCESS;
}

/* Termina o programa. */
int8_t bt_exit(bits_t ** bCtrl) {
    if (bCtrl == NULL)
	return ERR_BITCTRL_NULL;

    if ((*bCtrl)->bitArray != NULL)
	free((*bCtrl)->bitArray);

    free(*bCtrl);

    bCtrl = NULL;

    return SUCCESS;
}
