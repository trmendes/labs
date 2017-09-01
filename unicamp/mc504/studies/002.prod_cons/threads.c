#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "dvector.h"

#define STORAGESIZE 100
#define MAXPRODS 10

void *prod( void *ptr_storage );
void *cons( void *ptr_storage );

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int32_t argc, char **argv) {
    pthread_t thread1, thread2;
    int32_t ret1, ret2;

    dvector *storage = dv_create(100);
    printf("Endereco do deposito [corretor]: %p\n", storage);

    ret1 = pthread_create(&thread1, NULL, (void *)& prod, (void *) storage);
    if (ret1) {
	fprintf(stderr, "Error - pthread_create() return code %d\n", ret1);
	return EXIT_FAILURE;
    }

    ret2 = pthread_create(&thread2, NULL, (void *) & cons, (void *) storage);
    if (ret2) {
	fprintf(stderr, "Error - pthread_create() return code %d\n", ret2);
	return EXIT_FAILURE;
    }

    printf("pthread_create() for thread 1 returns: %d\n", ret1);
    printf("pthread_create() for thread 2 returns: %d\n", ret2);

    /* pthread_join will wait until the threads are complete */

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);

    return EXIT_SUCCESS;
}

void *prod(void *ptr_storage) {
    dvector *s;
    s = (dvector *) ptr_storage;
    printf("Endereco do deposito [produtor]: %p\n", s);
    int i = 1;
    while (i < MAXPRODS) {
	pthread_mutex_lock(&mutex);
	dv_insert_head(s, i);
//	dv_print(s, "Produtor produzindo...");
	printf("Produzindo: %d\r",i++);
	pthread_mutex_unlock(&mutex);
    }
    printf("Total da producao do dia: %d\n", i);
    pthread_mutex_lock(&mutex);
    printf("Produtos na fabrica     : %d\n", dv_len(s));
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *cons(void *ptr_storage) {
    dvector *s;
    s = (dvector *) ptr_storage;
    printf("Endereco do deposito [consumidor]: %p\n", s);
    int i = 1;
    while (i < MAXPRODS) {
	pthread_mutex_lock(&mutex);
	dv_remove_head(s);
//	dv_print(s, "Consumidor compulsivo consumindo...");
	printf("Consumindo: %d\r",i++);
	pthread_mutex_unlock(&mutex);
    }
    printf("Total de consumo do dia: %d\n",i);
    pthread_mutex_lock(&mutex);
    printf("Produtos na loja       : %d\n", dv_len(s));
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}