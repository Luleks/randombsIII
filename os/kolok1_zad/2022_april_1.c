#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !

int broj;
pthread_mutex_t mut;
pthread_cond_t full, empty;
bool isEmpty = true, run = true;

void* nit() {
    while (run) {
        pthread_mutex_lock(&mut);
        while (isEmpty)
            pthread_cond_wait(&full, &mut);
        if (not run)
            break;
        for (int i = 0; i < broj; i++) {
            printf("%d ", i);
            fflush(stdout);
            sleep(3);
        }
        isEmpty = true;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_t t;
    pthread_create(&t, NULL, nit, NULL);
    while (run) {
        pthread_mutex_lock(&mut);
        while (not isEmpty)
            pthread_cond_wait(&empty, &mut);
        printf("Unesite broj: ");
        scanf("%d", &broj);
        if (broj == 99)
            run = false;
        isEmpty = false;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mut);
    }
}