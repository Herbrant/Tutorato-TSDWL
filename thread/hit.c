#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/syscall.h>


int x = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void function_hit(void* arg){
    int hit;
    char threadname[16];

    sprintf(threadname, "Thread %s->", (char*)arg);

    for(int i = 0; ;i++){
        usleep(rand() % 10000 + 1);

        pthread_mutex_lock(&mutex);

        if(x >= 500){
            printf("%s x: %d, hit: %d\n", threadname, x, i);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        else
            x++;

        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t tA, tB;

    pthread_create(&tA, NULL, (void*) &function_hit, (void*)"a");
    pthread_create(&tB, NULL, (void*) &function_hit, (void*) "b");

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    printf("Finished.\n");
}