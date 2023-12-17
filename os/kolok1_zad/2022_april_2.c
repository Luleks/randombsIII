#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define size 10

int main() {
    srand(time(NULL));
    int pd12[2];
    int pd21[2];
    if (pipe(pd12) < 0) {
        perror("Error opening them legz 1-2 huehuehue");
        exit(1);
    }
    if (pipe(pd21) < 0) {
        perror("Error opening them legz 2-1 huehuehue");
        exit(1);
    }
    if (fork() != 0) {
        close(pd12[0]);
        close(pd21[1]);
        int nums[size];
        for (int i = 0; i < size; i++)
            nums[i] = 200 + rand() % 100;
        write(pd12[1], nums, size * sizeof(int));
        int count = read(pd21[0], nums, size * sizeof(int));
        for (int i = 0; i < count / sizeof(int); i++)
            printf("%d ", nums[i]);
        printf("\n");
        wait(NULL);
        close(pd12[1]);
        close(pd21[0]);
        return 0;
    }
    else {
        close(pd12[1]);
        close(pd21[0]);
        int nums[size];
        read(pd12[0], nums, size * sizeof(int));
        int k = 0;
        for (int i = 0; i < size; i++)
            if (nums[i] % 3 == 0)
                nums[k++] = nums[i] + 25;
        write(pd21[1], nums, k * sizeof(int));
    }
}