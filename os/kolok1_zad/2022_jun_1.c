#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define not !
#define and &&

int size;
int* niz;
pthread_mutex_t mut;
pthread_cond_t full, empty;
bool isEmpty = true;

void* sort() {
    pthread_mutex_lock(&mut);
    while (isEmpty)
        pthread_cond_wait(&full, &mut);

    for (int i = 1; i < size; i++) {
        int j = i - 1;
        int temp = niz[i];
        while(j >= 0 and niz[j] < temp) {
            niz[j + 1] = niz[j];
            j -= 1;
        }
        niz[j + 1] = temp;
    }
    isEmpty = true;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mut);
}

int main() {
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_mutex_init(&mut, NULL);
    pthread_t nit;
    pthread_create(&nit, NULL, sort, NULL);
    
    pthread_mutex_lock(&mut);
    while (not isEmpty)
        pthread_cond_wait(&empty, &mut);
    FILE* f = fopen("niz.txt", "r");
    fscanf(f, "%d", &size);
    niz = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        fscanf(f, "%d", &niz[i]);
    for (int i = 0; i < size; i++)
        printf("%d ", niz[i]);
    printf("\n");
    fclose(f);
    isEmpty = false;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mut);

    pthread_mutex_lock(&mut);
    while (not isEmpty)
        pthread_cond_wait(&empty, &mut);
    for (int i = 0; i < size; i++)
        printf("%d ", niz[i]);
    printf("\n");
    free(niz);
    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
}