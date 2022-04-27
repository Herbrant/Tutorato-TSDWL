#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *threadF(void *vargp) {
    sleep(1);
    printf("Ehi, I'm the thread\n");
}


int main(void) {
    pthread_t pthread_id;
    printf("Creating threads...\n");
    pthread_create(&pthread_id, NULL, threadF, NULL);
    pthread_join(pthread_id, NULL);

    printf("Thread stopped\n");
}