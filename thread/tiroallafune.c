#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#define MAX_WIN 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int posizione = 0, vittorie_tp0 = 0, vittorie_tp1 = 0;

void thread_function(void* arg){
    int recupero, forza;
    
    for(;;){
        recupero = rand() % 4;
        forza = rand() % 6;

        pthread_mutex_lock(&mutex);

        if(vittorie_tp0 >= MAX_WIN || vittorie_tp1 >= MAX_WIN){
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        if(strcmp((char*)arg, "0") == 0){
            if(posizione >= 10){
                vittorie_tp1++;
                posizione = 0;
                printf("Il thread 1 ha vinto! Vittorie tp1: %d\n", vittorie_tp1);
                pthread_cond_signal(&cond);
            }
            else{
                posizione -= forza;
                if(posizione <= -10)
                    pthread_cond_wait(&cond, &mutex);
            }
    
        }
        else{
            if(posizione <= -10){
                vittorie_tp0++;
                posizione = 0;
                printf("Il thread 0 ha vinto! Vittorie tp0: %d\n", vittorie_tp0);
                pthread_cond_signal(&cond);
            }
            else{
                posizione += forza;
                if(posizione >= 10)
                    pthread_cond_wait(&cond, &mutex);
            }
        }

        pthread_mutex_unlock(&mutex);

        sleep(recupero);
    }
}

int main(void){
    pthread_t th0, th1;

    srand(time(NULL));
    pthread_create(&th0, NULL, (void*) &thread_function, (void*) "0");
    pthread_create(&th1, NULL, (void*) &thread_function, (void*) "1");

    pthread_join(th0, NULL);
    pthread_join(th1, NULL);

    if(vittorie_tp0 > vittorie_tp1)
        printf("Il thread 0 vince!\n");
    else
        printf("Il thread 1 vince!\n");

    exit(0);
}