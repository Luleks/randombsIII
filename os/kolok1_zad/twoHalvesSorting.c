/* Prva nit sortira prvu polovinu niza u rastucem poretku, a druga drugu polovinu u opadajucem, 
main puni niz random brojevima */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define not !
#define size 8

int niz[size];
pthread_mutex_t access1, access2;
pthread_cond_t full, sorted1, sorted2;
bool isEmpty = true, isSorted1 = false, isSorted2 = false;

void* first_half() {
    pthread_mutex_lock(&access1);
    while (isEmpty)
        pthread_cond_wait(&full, &access1);
    for (int i = size / 2 - 1; i >= 1; i--)
        for (int j = 0; j < i; j++)
            if (niz[j] > niz[j + 1]) {
                int temp = niz[j];
                niz[j] = niz[j + 1];
                niz[j + 1] = temp;
            }
    isSorted1 = true;
    pthread_cond_signal(&sorted1);
    pthread_mutex_unlock(&access1);
}

void* second_half() {
    pthread_mutex_lock(&access2);
    while (isEmpty)
        pthread_cond_wait(&full, &access2);
    for (int i = size - 1; i >= size / 2; i--)
        for (int j = size / 2; j < i; j++)
            if (niz[j] < niz[j + 1]) {
                int temp = niz[j];
                niz[j] = niz[j + 1];
                niz[j + 1] = temp;
            }
    isSorted2 = true;
    pthread_cond_signal(&sorted2);
    pthread_mutex_unlock(&access2);
}

int main() {
    srand(time(0));
    pthread_mutex_init(&access1, NULL);
    pthread_mutex_init(&access2, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&sorted1, NULL);
    pthread_cond_init(&sorted2, NULL);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, first_half, NULL);
    pthread_create(&t2, NULL, second_half, NULL);

    pthread_mutex_lock(&access1);
    pthread_mutex_lock(&access2);
    for (int i = 0; i < size; i++)
        niz[i] = rand() % 50;
    for (int i = 0; i < size; i++)
        printf("%d ", niz[i]);
    printf("\n");
    isEmpty = false;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&access1);
    pthread_mutex_unlock(&access2);

    pthread_mutex_lock(&access1);
    while (not isSorted1)
        pthread_cond_wait(&sorted1, &access1);
    pthread_mutex_lock(&access2);
    while (not isSorted2)
        pthread_cond_wait(&sorted2, &access2);
    for (int i = 0; i < size; i++)
        printf("%d ", niz[i]);
    printf("\n");
    pthread_mutex_unlock(&access1);
    pthread_mutex_unlock(&access2);

    pthread_mutex_destroy(&access1);
    pthread_mutex_destroy(&access2);
    pthread_cond_destroy(&sorted1);
    pthread_cond_destroy(&sorted2);
    pthread_cond_destroy(&full);
}
