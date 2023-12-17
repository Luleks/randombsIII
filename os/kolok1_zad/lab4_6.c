#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening the pipe");
        exit(1);
    }
    if (fork() != 0) {
        close(pd[0]);
        for (int i = 0; i < 25; i++) {
            char random = rand() % 255;
            write(pd[1], &random, 1);
        }
        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        FILE* f = fopen("charz.txt", "w");
        for (int i = 0; i < 25; i++) {
            char readed;
            read(pd[0], &readed, 1);
            fprintf(f, "%c\n", readed);
        }
        close(pd[0]);
    }
}