#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <wait.h>

#define not !

int buf[10];
pthread_mutex_t mut;
pthread_cond_t full, empty;
bool isEmpty = true, run = true;
int k = 0;

void* nit() {
    while(run) {
        pthread_mutex_lock(&mut);
        while(not isEmpty)
            pthread_cond_wait(&empty, &mut);
        if (not run)
            break;
        buf[k] = rand() % 200;
        // sleep(1);
        k = (k + 1) % 10;
        if (k == 0) {
            isEmpty = false;
            pthread_cond_signal(&full);
        }        
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    srand(time(0));
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_t t;
    pthread_create(&t, NULL, nit, NULL);
    while (run) {
        pthread_mutex_lock(&mut);
        while (isEmpty)
            pthread_cond_wait(&full, &mut);
        int s = 0;
        for (int i = 0; i < 10; i++)
            s += buf[i];
        if (s > 1000)
            run = false;
        if (s > 800)
            printf("%d>800\n", s);
        else
            printf("%d<=800\n", s);
        isEmpty = true;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mut);
    }
}