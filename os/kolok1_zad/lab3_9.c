#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t sortedKolone, sortedVrste;
sem_t kolonaNext, vrstaNext;
int mat[N][N];

void* sort_vrste() {
    for (int i = 0; i < N; i++) {
        sem_wait(&vrstaNext);
        for (int j = 1; j < N; j++) {
            int temp = mat[i][j];
            int k = j - 1;
            while (k >= 0 && mat[i][k] > temp) {
                mat[i][k + 1] = mat[i][k];
                k -= 1;
            }
            mat[i][k + 1] = temp;
        }
        sem_post(&kolonaNext);
    }
    sem_post(&sortedVrste);
}

void* sort_kolone() {
    for (int i = 0; i < N; i++) {
        sem_wait(&kolonaNext);
        for (int j = 1; j < N; j++) {
            int temp = mat[j][i];
            int k = j - 1;
            while (k >= 0 && mat[k][i] > temp) {
                mat[k + 1][i] = mat[k][i];
                k -= 1;
            }
            mat[k + 1][i] = temp;
        }
        sem_post(&vrstaNext);
    }
    sem_post(&sortedKolone);
}

int main() {
    sem_init(&sortedKolone, 0, 0);
    sem_init(&sortedVrste, 0, 0);
    sem_init(&kolonaNext, 0, 0);
    sem_init(&vrstaNext, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, sort_vrste, NULL);
    pthread_create(&t2, NULL, sort_kolone, NULL);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = 10 + rand() % 90;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    } 
    sem_post(&vrstaNext);

    sem_wait(&sortedVrste);
    sem_wait(&sortedKolone);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    } 

    sem_destroy(&kolonaNext);
    sem_destroy(&vrstaNext);
    sem_destroy(&sortedKolone);
    sem_destroy(&sortedVrste);
}