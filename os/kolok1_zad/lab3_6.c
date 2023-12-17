#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !

pthread_mutex_t mut;
pthread_cond_t malo, veliko;
bool malo_turn = true;

void* print_veliko() {
    for (char i = 'A'; i <= 'Z'; i++) {
        pthread_mutex_lock(&mut);
        while (malo_turn)
            pthread_cond_wait(&veliko, &mut);
        printf("%c", i);
        malo_turn = true;
        pthread_cond_signal(&malo);
        pthread_mutex_unlock(&mut);
    }
}

int main() {
    pthread_cond_init(&malo, NULL);
    pthread_cond_init(&veliko, NULL);
    pthread_mutex_init(&mut, NULL);
    pthread_t velika_slova;
    pthread_create(&velika_slova, NULL, print_veliko, NULL);

    for (char i = 'a'; i <= 'z'; i++) {
        pthread_mutex_lock(&mut);
        while (not malo_turn)
            pthread_cond_wait(&malo, &mut);
        printf("%c", i);
        malo_turn = false;
        pthread_cond_signal(&veliko);
        pthread_mutex_unlock(&mut);
    }

    pthread_join(velika_slova, NULL);
    pthread_cond_destroy(&malo);
    pthread_cond_destroy(&veliko);
    pthread_mutex_destroy(&mut);
}