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
    int32_t collision, oindex = 0;
    unsigned long key = hs_hash_djb2(data);
    int32_t index = hs_hash1(key, hash->hashsize);

    node = (data_t *) calloc(1, sizeof(data_t));
    strncpy(node->data, data, CHARMAX);

    if (hash->array[index] == (data_t *) NULL) {
	node->idx = hash->hashidx++;
	hash->array[index] = node;
    } else {
	oindex = index;
	collision = hash->hashsize - (hs_hash2(key, hash->hashsize));

	if (collision == 0)
	    collision = 1;

	while (hash->array[index] != (data_t *) NULL) {
	    index = (index + collision) % hash->hashsize;
	    if (index == oindex) {
		free(node);
		return ERR_NO_SPACE;
	    }
	}

	node->idx = oindex;
	hash->array[index] = node;
    }

    return SUCCESS;
}


void hs_find_key( hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	    return;

    data_t * node = (data_t *) NULL;
    unsigned long key;
    int32_t index, oindex, collision;

    key = hs_hash_djb2(data);
    index = hs_hash1(key, hash->hashsize);
    node = hash->array[index];
    oindex = index;
    collision = hash->hashsize - (hs_hash2(key, hash->hashsize));
    if (collision == 0)
	collision = 1;

    while (node != (data_t *) NULL) {
	if (strcmp(node->data, data) == 0) {
	    break;
	} else {
	    index = (index + collision) % hash->hashsize;
	    node = hash->array[index];

	    if (index == oindex) {
		break;
	    }
	}
    }

    if (node == (data_t *) NULL)
	printf("nao encontrado\n");
    else {
	printf("encontrado %d\n", node->idx);
    }
}

int32_t hs_remove_key( hash_t * hash, char * data) {
    if (hash == (hash_t *) NULL)
	return ERR_HEAP_NULL;

    unsigned long key;
    int32_t collision, index, oindex;
    data_t * node = (data_t *) NULL;

    key = hs_hash_djb2(data);
    index = hs_hash1(key, hash->hashsize);
    node = hash->array[index];
    oindex = index;
    collision = hash->hashsize - (hs_hash2(key, hash->hashsize));
    if (collision == 0)
	collision = 1;

    while (node != (data_t *) NULL) {
	if (strcmp(node->data, data) == 0) {
	    free(hash->array[index]);
	    hash->array[index] = (data_t *) NULL;
	    break;
	} else {
	    index = (index + collision) % hash->hashsize;
	    node = hash->array[index];
	    if (index == oindex)
		break;
	}
    }

    return SUCCESS;
}
/* http://www.cse.yorku.ca/~oz/hash.html */
unsigned long hs_hash_djb2(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
	hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

int32_t hs_hash1(unsigned long key, size_t size) {
    return key % size;
}

int32_t hs_hash2(unsigned long key, size_t size) {
    return (key + 10) % size;
}
