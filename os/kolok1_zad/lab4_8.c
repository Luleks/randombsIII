#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pd[2];
    if (pipe(pd) < 0)
        exit(1);
    if (fork() != 0){
        close(pd[0]);
        for (int i = 0; i < 20; i++) {
            int rando = 10 + rand() % 191;
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
            if (num % 2 == 0)
                printf("%d\n", num);
            else
                printf("-1..\n");
        }
        close(pd[0]);
    }
}