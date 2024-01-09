#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>

int main_pid;
int child_pid;

void sigusr1_handler() {
    printf("User\n");
    int nums[10];
    FILE* f = fopen("prenos2.dat", "rb");
    fread(nums, sizeof(int), 10, f);
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    fclose(f);
    printf("\n");
    kill(main_pid, SIGUSR2);
}

void sigusr2_handler() {
    printf("Generator\n");
    FILE* f = fopen("prenos2.dat", "wb");
    int nums[10];
    for (int i = 0; i < 10; i++) {
        nums[i] = 10 + rand() % 90;
    }
    fwrite(nums, sizeof(int), 10, f);
    fclose(f);
    kill(child_pid, SIGUSR1);
}

int main() {
    if ((child_pid = fork()) != 0) {
        signal(SIGUSR2, sigusr2_handler);
        for (int i = 0; i < 3; i++)
            pause();
        wait(NULL);
    }
    else {
        main_pid = getppid();
        signal(SIGUSR1, sigusr1_handler);
        kill(main_pid, SIGUSR2);
        for (int i = 0; i < 3; i++)
            pause();
    }
}