#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define not !
#define or ||

pthread_mutex_t mut;
pthread_cond_t prva, druga, mian;
bool prva_turn = false, druga_turn = false;
int niz[5];

void* prva_nit() {
    pthread_mutex_lock(&mut);
    while (not prva_turn)
        pthread_cond_wait(&prva, &mut);
    for (int i = 0; i < 5; i++)
        if (niz[i] < 0)
            niz[i] = -niz[i];
    prva_turn = false;
    druga_turn = true;
    pthread_cond_signal(&druga);
    pthread_mutex_unlock(&mut);

}

void* druga_nit() {
    pthread_mutex_lock(&mut);
    while (not druga_turn)
        pthread_cond_wait(&druga, &mut);
    int s = 0;
    for (int i = 0; i < 5; i++)
        s += niz[i];
    niz[0] = s / 5;
    druga_turn = false;
    pthread_cond_signal(&mian);
    pthread_mutex_unlock(&mut);
}

int main() {
    srand(time(0));
    pthread_cond_init(&prva, NULL);
    pthread_cond_init(&druga, NULL);
    pthread_cond_init(&mian, NULL);
    pthread_mutex_init(&mut, NULL);
    pthread_t nit1, nit2;
    pthread_create(&nit1, NULL, prva_nit, NULL);
    pthread_create(&nit2, NULL, druga_nit, NULL);

    pthread_mutex_lock(&mut);
    for (int i = 0; i < 5; i++) {
        niz[i] = rand() % 21 - 10;
    }
    for (int i = 0; i < 5; i++)
        printf("%d ", niz[i]);
    printf("\n");
    prva_turn = true;
    pthread_cond_signal(&prva);
    pthread_mutex_unlock(&mut);

    pthread_mutex_lock(&mut);
    while (prva_turn or druga_turn)
        pthread_cond_wait(&mian, &mut);
    for (int i = 0; i < 5; i++)
        printf("%d ", niz[i]);
    printf("\n");
    pthread_cond_destroy(&prva);
    pthread_cond_destroy(&druga);
    pthread_cond_destroy(&mian);
    pthread_mutex_destroy(&mut);
}