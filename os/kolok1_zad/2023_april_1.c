#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !
#define size 10

int buf[size];
pthread_mutex_t mutEven, mutOdd;
pthread_cond_t evenFull, evenEmpty, oddFull, oddEmpty;
bool even_empty = true, odd_empty = true;

void* parna_nit() {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutEven);
        while (not even_empty)
            pthread_cond_wait(&evenEmpty, &mutEven);
        for (int j = 0; j < size; j+=2)
            buf[j] = rand() % 300;
        even_empty = false;
        pthread_cond_signal(&evenFull);
        pthread_mutex_unlock(&mutEven);
    }
}

void* neparna_nit() {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutOdd);
        while (not odd_empty)
            pthread_cond_wait(&oddEmpty, &mutOdd);
        for (int j = 1; j < size; j+=2)
            buf[j] = 300 + rand() % 100;
        odd_empty = false;
        pthread_cond_signal(&oddFull);
        pthread_mutex_unlock(&mutOdd);
    }
}

int main() {
    pthread_mutex_init(&mutEven, NULL);
    pthread_mutex_init(&mutOdd, NULL);
    pthread_cond_init(&evenFull, NULL);
    pthread_cond_init(&evenEmpty, NULL);
    pthread_cond_init(&oddFull, NULL);
    pthread_cond_init(&oddEmpty, NULL);
    pthread_t even_t, odd_t;
    pthread_create(&even_t, NULL, parna_nit, NULL);
    pthread_create(&odd_t, NULL, neparna_nit, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutEven);
        while (even_empty)
            pthread_cond_wait(&evenFull, &mutEven);
        pthread_mutex_lock(&mutOdd);
        while (odd_empty)
            pthread_cond_wait(&oddFull, &mutOdd);
        int s = 0;
        for (int i = 0; i < size; i++)
            s += buf[i];
        if (s > 2000)
            printf("%d>2000\n", s);
        else
            printf("%d<=2000\n", s);
        odd_empty = true;
        even_empty = true;
        pthread_cond_signal(&evenEmpty);
        pthread_cond_signal(&oddEmpty);
        pthread_mutex_unlock(&mutEven);
        pthread_mutex_unlock(&mutOdd);
        sleep(2);
    }

    pthread_mutex_destroy(&mutEven);
    pthread_mutex_destroy(&mutOdd);
    pthread_cond_destroy(&oddEmpty);
    pthread_cond_destroy(&oddFull);
    pthread_cond_destroy(&evenEmpty);
    pthread_cond_destroy(&evenFull);
}