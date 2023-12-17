#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>

void clear_buf(char niz[101]) {
    for (int i = 0; i < 100; i++)
        niz[i] = '\0';
}

int main(int argc, char* argv[]) {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening the pipe");
        exit(1);
    }
    if (fork() != 0) {
        close(pd[0]);
        FILE* f = fopen(argv[1], "r");
        char niz[101];
        clear_buf(niz);
        while (!feof(f)) {
            fgets(niz, 100, f);
            write(pd[1], niz, strlen(niz));
            clear_buf(niz);
        }
        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        FILE* f = fopen(argv[2], "w");
        char niz[101];
        clear_buf(niz);
        int count = read(pd[0], niz, 100);
        fputs(niz, f);
        while (count == 100) {
            count = read(pd[0], niz, 100);
            fputs(niz, f);
            clear_buf(niz);
        }
        fclose(f);
        close(pd[0]);
    }
}