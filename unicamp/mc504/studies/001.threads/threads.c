#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define WAITT1 50
#define WAITT2 1

typedef struct sdata {
    int32_t timetowait;
    const char *msgtoprint;
} data;

void *print_message_function( void *ptr);

int main(int32_t argc, char **argv) {
    pthread_t thread1, thread2;
    int32_t ret1, ret2;

    data t1d, t2d;

    t1d.msgtoprint = "Hi There! I'm Thread #1!";
    t1d.timetowait = WAITT1;

    t2d.msgtoprint = "Hey!! Thread #2 here!";
    t2d.timetowait = WAITT2;

    ret1 = pthread_create(&thread1, NULL, (void *)& print_message_function, (void *) &t1d);
    if (ret1) {
	fprintf(stderr, "Error - pthread_create() return code %d\n", ret1);
	return EXIT_FAILURE;
    }

    ret2 = pthread_create(&thread2, NULL, (void *) &print_message_function, (void *) &t2d);
    if (ret2) {
	fprintf(stderr, "Error - pthread_create() return code %d\n", ret2);
	return EXIT_FAILURE;
    }

    printf("pthread_create() for thread 1 returns: %d\n", ret1);
    printf("pthread_create() for thread 2 returns: %d\n", ret2);

    /* pthread_join will wait until the threads are complete */

    pthread_join(thread2, NULL);
    printf("Join 2 livre\n");
    pthread_join(thread1, NULL);
    printf("Join 1 livre\n");

    return EXIT_SUCCESS;
}

void *print_message_function(void *ptr) {
    data *d;
    d = (data *) ptr;
    sleep(d->timetowait);
    printf("%s\n", d->msgtoprint);
    pthread_exit(0);
}