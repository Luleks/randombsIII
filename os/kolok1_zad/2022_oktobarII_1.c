#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#define not !

pthread_mutex_t mut;
pthread_cond_t full, empty;
bool isEmpty = true, run = true;
char num[5];

void clear_buf() {
    for (int i = 0; i < 5; i++)
        num[i] = '\0';
}

void* nit() {
    while (run) {
        pthread_mutex_lock(&mut);
        while (isEmpty)
            pthread_cond_wait(&full, &mut);
        if (not run)
            break;
        for (int i = 0; i < atoi(num); i++)
            printf("%d ", i);
        printf("\n");
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
        clear_buf();
        printf("Unesite broj ili KRAJ: ");
        scanf("%s", num);
        if (strcmp(num, "KRAJ") == 0)
            run = false;
        isEmpty = false;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mut);
    }

    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    pthread_mutex_destroy(&mut);
}
