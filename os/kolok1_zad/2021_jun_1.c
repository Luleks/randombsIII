#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#define not !
#define and &&

int N = 0;
char recenica[200];
char* reci[20];
pthread_mutex_t access;
pthread_cond_t sort_redy, print_redy, kraj_redy;
bool sortRedy = false, printRedy = false, krajRedy = false;

void* sort_recenica() {
    pthread_mutex_lock(&access);
    while (not sortRedy)
        pthread_cond_wait(&sort_redy, &access);

    int i = 0;
    char* token = strtok(recenica, " ");
    while (token != NULL) {
        reci[i++] = token;
        token = strtok(NULL, " ");
    }
    for (int j = 1; j < i; j++) {
        char* temp = reci[j];
        int k = j - 1;
        while (k >= 0 and strcmp(temp, reci[k]) > 0) {
            reci[k + 1] = reci[k];
            k -= 1;
        }
        reci[k + 1] = temp;
    }
    N = i;
    printRedy = true;
    pthread_cond_signal(&print_redy);
    pthread_mutex_unlock(&access);
}

void* print_recenica() {
    pthread_mutex_lock(&access);
    while (not printRedy)
        pthread_cond_wait(&print_redy, &access);
    reci[0][0] = 'A' + reci[0][0] - 'a';
    for (int i = 0; i < N; i++)
        printf("%s ", reci[i]);
    krajRedy = true;
    pthread_cond_signal(&kraj_redy);
    pthread_mutex_unlock(&access);
}

int main() {
    pthread_cond_init(&sort_redy, NULL);
    pthread_cond_init(&print_redy, NULL);
    pthread_cond_init(&kraj_redy, NULL);
    pthread_mutex_init(&access, NULL);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, sort_recenica, NULL);
    pthread_create(&t2, NULL, print_recenica, NULL);

    fgets(recenica, 200, stdin);
    recenica[strcspn(recenica, "\n")] = '\0';
    sortRedy = true;
    pthread_cond_signal(&sort_redy);
    
    pthread_mutex_lock(&access);
    while (not krajRedy)
        pthread_cond_wait(&kraj_redy, &access);

    printf("\nKRAJ");
    pthread_cond_destroy(&sort_redy);
    pthread_cond_destroy(&kraj_redy);
    pthread_cond_destroy(&print_redy);
    pthread_mutex_destroy(&access);
}