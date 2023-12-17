#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

int N;
int* nums;
sem_t sorted12, sorted22, access12, access22;

void* sort12() {
    sem_wait(&access12);
    for (int i = 1; i < N / 2; i++) {
        int temp = nums[i];
        int j = i - 1;
        while (j >= 0 && temp < nums[j]) {
            nums[j + 1] = nums[j];
            j -= 1;
        }
        nums[j + 1] = temp;
    }
    sem_post(&sorted12);
}

void* sort22() {
    sem_wait(&access22);
    for (int i = N / 2 + 1; i < N; i++) {
        int temp = nums[i];
        int j = i - 1;
        while (j >= N / 2 && temp > nums[j]) {
            nums[j + 1] = nums[j];
            j -= 1;
        }
        nums[j + 1] = temp;
    }
    sem_post(&sorted22);
}

int main() {
    sem_init(&access12, 0, 0);
    sem_init(&access22, 0, 0);
    sem_init(&sorted12, 0, 0);
    sem_init(&sorted22, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, sort12, NULL);
    pthread_create(&t2, NULL, sort22, NULL);
    printf("N: ");
    scanf("%d", &N);
    nums = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        nums[i] = rand() % 10;
    for (int i = 0; i < N; i++)
        printf("%d ", nums[i]);
    printf("\n");
    sem_post(&access12);
    sem_post(&access22);

    sem_wait(&sorted12);
    sem_wait(&sorted22);
    for (int i = 0; i < N; i++)
        printf("%d ", nums[i]);
    
    printf("\n");
    free(nums);

    sem_destroy(&sorted12);
    sem_destroy(&sorted22);
    sem_destroy(&access12);
    sem_destroy(&access22);
}