#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


#define N 5
#define not !

int niz[N];
pthread_mutex_t mut;
pthread_cond_t next_num, print_nums;
bool next_number = true;

void* print_t() {
    for (int j = 0; j < 10; j++) {
        pthread_mutex_lock(&mut);
        while (next_number)
            pthread_cond_wait(&print_nums, &mut);
        int s = 0;
        for (int i = 0; i < N; i++)
            s += niz[i];
        if (s % 2 == 0)
            for (int i = 0; i < N; i++)
                printf("%d ", niz[i]);
        printf("\n");
        next_number = true;
        pthread_cond_signal(&next_num);
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    for (int i = 0; i < N; i++)
        niz[i] = 0;
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&next_num, NULL);
    pthread_cond_init(&print_nums, NULL);
    pthread_t t1;
    pthread_create(&t1, NULL, print_t, NULL);
    for (int j = 0; j < 10; j++) {
        pthread_mutex_lock(&mut);
        while (not next_number)
            pthread_cond_wait(&next_num, &mut);
        niz[rand() % N] = rand() % 21 - 10;
        next_number = false;
        pthread_cond_signal(&print_nums);
        pthread_mutex_unlock(&mut);
        sleep(3);
    }

    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&next_num);
    pthread_cond_destroy(&print_nums);
}