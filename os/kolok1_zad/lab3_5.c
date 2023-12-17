#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !

pthread_mutex_t mut;
pthread_cond_t paran, neparan;
bool paran_turn = false;
FILE* f;

void* neparni() {
    for (int i = 1; i <= 20; i+=2) {
        pthread_mutex_lock(&mut);
        while(paran_turn)
            pthread_cond_wait(&neparan, &mut);
        fprintf(f, "%d\n", i);
        paran_turn = true;
        pthread_cond_signal(&paran);
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    pthread_cond_init(&paran, NULL);
    pthread_cond_init(&neparan, NULL);
    pthread_mutex_init(&mut, NULL);
    f = fopen("brojevi.txt", "w");
    pthread_t thr;
    pthread_create(&thr, NULL, neparni, NULL);

    for (int i = 2; i <= 20; i+=2) {
        pthread_mutex_lock(&mut);
        while(not paran_turn)
            pthread_cond_wait(&paran, &mut);
        fprintf(f, "%d\n", i);
        paran_turn = false;
        pthread_cond_signal(&neparan);
        pthread_mutex_unlock(&mut);
    }

    pthread_join(thr, NULL);

    pthread_cond_destroy(&paran);
    pthread_cond_destroy(&neparan);
    pthread_mutex_destroy(&mut);
}