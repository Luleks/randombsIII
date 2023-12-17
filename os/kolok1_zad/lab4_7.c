#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pd[2];
    if (pipe(pd) < 0)
        exit(1);
    
    if (fork() != 0) {
        close(pd[0]);
        for (int i = 0; i < 50; i++) {
            int rando = rand() % 69;
            write(pd[1], &rando, sizeof(int));
        }
        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        for (int i = 0; i < 50; i++) {
            int num;
            read(pd[0], &num, sizeof(int));
            printf("%d ", num);
        }
        printf("\n");
        close(pd[0]);
    }
}