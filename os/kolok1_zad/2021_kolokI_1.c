#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !
#define and &&

int* niz;
int N;
pthread_mutex_t mutEven, mutOdd;
pthread_cond_t evenFull, evenEmpty, oddFull, oddEmpty;
bool isEmpty = true, isDone1 = false, isDone2 = false;

void* nit_odd() {
    pthread_mutex_lock(&mutOdd);
    while (isEmpty)
        pthread_cond_wait(&oddFull, &mutOdd);
    for (int i = 1; i < N; i+=2)
        niz[i] += 2;
    isDone1 = true;
    pthread_cond_signal(&oddEmpty);
    pthread_mutex_unlock(&mutOdd);
}

void* nit_even() {
    pthread_mutex_lock(&mutEven);
    while (isEmpty)
        pthread_cond_wait(&evenFull, &mutEven);
    
    for (int i = 2; i < N; i+=2) {
        int temp = niz[i];
        int j = i - 2;
        while (j >= 0 and niz[j] < temp) {
            niz[j + 2] = niz[j];
            j -= 2;
        }
        niz[j + 2] = temp;
    }

    isDone2 = true;
    pthread_cond_signal(&evenEmpty);
    pthread_mutex_unlock(&mutEven);
}

int main() {
    pthread_mutex_init(&mutEven, NULL);
    pthread_mutex_init(&mutOdd, NULL);
    pthread_cond_init(&evenEmpty, NULL);
    pthread_cond_init(&evenFull, NULL);
    pthread_cond_init(&oddEmpty, NULL);
    pthread_cond_init(&oddFull, NULL);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, nit_odd, NULL);
    pthread_create(&t2, NULL, nit_even, NULL);

    pthread_mutex_lock(&mutEven);
    pthread_mutex_lock(&mutOdd);
    printf("N: ");
    scanf("%d", &N);
    niz = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        printf("niz[%d]: ", i);
        scanf("%d", &niz[i]);
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", niz[i]);
    }
    printf("\n");
    isEmpty = false;
    pthread_cond_signal(&evenFull);
    pthread_cond_signal(&oddFull);
    pthread_mutex_unlock(&mutEven);
    pthread_mutex_unlock(&mutOdd);

    pthread_mutex_lock(&mutOdd);
    while (not isDone1)
        pthread_cond_wait(&oddEmpty, &mutOdd);
    pthread_mutex_lock(&mutEven);
    while (not isDone2)
        pthread_cond_wait(&evenEmpty, &mutEven);
    for (int i = 0; i < N; i++) {
        printf("%d ", niz[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&mutEven);
    pthread_mutex_destroy(&mutOdd);
    pthread_cond_destroy(&oddEmpty);
    pthread_cond_destroy(&evenEmpty);
    pthread_cond_destroy(&oddFull);
    pthread_cond_destroy(&evenFull);
}