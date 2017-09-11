#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "dvector.h"
#include "trace.h"

#define STORAGESIZE     50
#define MAXPRODS        20
#define OPENTHESTOREAT  10
#define NTHREADS 30

void *prod( void *ptr_storage );
void *cons( void *ptr_storage );

pthread_mutex_t mutex           = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
int32_t prod_count = 0;
int32_t prod_cons = 0;

int32_t main(int32_t argc, char **argv) {
    pthread_t thread[NTHREADS];
    int32_t ret, i;

    dvector *storage = dv_create(STORAGESIZE);
    printf("Endereco do deposito [corretor]: %p\n", storage);

    for (i = 0; i < NTHREADS; i++) {
	if (i % 2 == 0)
	    ret = pthread_create(&thread[i], NULL, (void *)& cons, (void *) storage);
	else
	    ret = pthread_create(&thread[i], NULL, (void *)& prod, (void *) storage);

	printf("pthread_create() for thread %d returns: %d\n", i, ret);
	if (ret) {
	    fprintf(stderr, "Error - pthread_create() return code %d\n", ret);
	    return EXIT_FAILURE;
	}
    }

    for (i = 0; i < NTHREADS; i++) {
	pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}

void *prod(void *ptr_storage) {
    dvector *s;
    s = (dvector *) ptr_storage;
    int32_t keep = 1;
    printf("Endereco do deposito [produtor]: %p\n", s);
    while (keep != 0) {
	pthread_mutex_lock(&mutex);

	dv_insert_head(s, prod_count);
	printf("%sProduzindo: %d%s\n",ANSI_COLOR_RED, ++prod_count, ANSI_COLOR_RESET);

	if (prod_count == MAXPRODS) {
	    keep = 0;
	    pthread_cond_signal( &condition_var );
	}

	if (dv_len(s) >= OPENTHESTOREAT) {
	    pthread_cond_signal( &condition_var );
	}

	pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void *cons(void *ptr_storage) {
    dvector *s;
    int32_t keep = 1;
    s = (dvector *) ptr_storage;
    printf("Endereco do deposito [consumidor]: %p\n", s);
    while (keep != 0) {
	pthread_mutex_lock(&mutex);

	while (dv_len(s) == 0) {
	    pthread_cond_wait(&condition_var, &mutex);
	}

	dv_remove_head(s);
	printf("%sConsumindo: %d\n%s",ANSI_COLOR_GREEN, ++prod_cons, ANSI_COLOR_RESET);

	if (prod_cons == MAXPRODS) {
	    keep = 0;
	}

	pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}