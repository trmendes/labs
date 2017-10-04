#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hash_t * hs_create(int32_t hashsize) {
    hash_t * h = (hash_t *) calloc(1, sizeof(hash_t));
    h->hashsize = hashsize;
    h->array = (data_t **) calloc(hashsize, sizeof(data_t *));
    return h;
}

void hs_destroy(hash_t ** hash) {
    if (*hash == (hash_t *) NULL)
	return;

    int32_t i;

    for (i = 0; i < (*hash)->hashsize; ++i) {
	if ((*hash)->array[i] != (data_t *) NULL)
	    free((*hash)->array[i]);
    }

    free((*hash)->array);
    free(*hash);
    *hash = NULL;
}

int8_t hs_insert_key(hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	    return ERR_HEAP_NULL;

    data_t * node = (data_t *) NULL;
    int32_t index = hs_hash_sum(hash, data);
    int32_t collision, oindex = 0;

    if (index < 0)
	return index;

    node = (data_t *) calloc(1, sizeof(data_t));
    strcpy(node->data, data);

    if (hash->array[index] == (data_t *) NULL) {
	hash->array[index] = node;
    } else {
	oindex = index;
	collision = hash->hashsize - (hs_hash_djb2(data) % hash->hashsize);

	if (collision == 0)
	    collision = 1;

	while (hash->array[index] != (data_t *) NULL) {
	    index = (index + collision) % hash->hashsize;
	    if (index == oindex)
		return ERR_NO_SPACE;
	}

	hash->array[index] = node;
    }

    return SUCCESS;
}

int32_t hs_hash_sum(hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	    return ERR_HEAP_NULL;

    uint32_t i;
    int32_t sum;

    for (i = 0; i < strlen(data); ++i) {
	sum += data[i];
    }

    return sum % hash->hashsize;
}

void hs_find_key( hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	    return;

    int32_t collision, index, oindex, i = 0;
    data_t * node = (data_t *) NULL;

    index = hs_hash_sum(hash, data);
    node = hash->array[index];
    oindex = index;
    collision = hash->hashsize - (hs_hash_djb2(data) % hash->hashsize);

    while (node != (data_t *) NULL) {
	if (strcmp(node->data, data) == 0) {
	    ++i;
	}

	index = (index + collision) % hash->hashsize;
	node = hash->array[index];

	if (index == oindex) {
	    break;
	}
    }

    if (i == 0)
	printf("nao encontrado\n");
    else
	printf("encontrado %d\n", i);
}

int32_t hs_remove_key( hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	return ERR_HEAP_NULL;

    int32_t collision, index, oindex;
    data_t * node = (data_t *) NULL;

    index = hs_hash_sum(hash, data);
    node = hash->array[index];
    oindex = index;
    collision = hash->hashsize - (hs_hash_djb2(data) % hash->hashsize);
    if (collision == 0)
	collision = 1;

    while (node != (data_t *) NULL) {
	if (strcmp(node->data, data) == 0) {
	    free(hash->array[index]);
	    hash->array[index] = (data_t *) NULL;
	}
	index = (index + collision) % hash->hashsize;
	node = hash->array[index];

	if (index == oindex)
	    break;
    }

    return SUCCESS;
}

unsigned long hs_hash_djb2(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
	hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}
