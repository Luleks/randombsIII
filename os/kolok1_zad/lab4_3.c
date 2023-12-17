#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pd[2];
    if (pipe(pd) < 0)
        exit(1);
    if (fork() != 0) {
        close(pd[0]);
        for (int i = 0; i < 20; i++) {
            int rando = 100 + rand() % 200;
            write(pd[1], &rando, sizeof(int));
        }
        wait(NULL);
        close(pd[1]);
    }
    else {
        close(pd[1]);
        for (int i = 0; i < 20; i++) {
            int num;
            read(pd[0], &num, sizeof(int));
            if (num % 3 == 0)
                printf("%d ", num);
        }
        printf("\n");
        close(pd[0]);
    }
}