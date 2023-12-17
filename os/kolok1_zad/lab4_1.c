#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <wait.h>

int main() {
    srand(time(NULL));
    int pd12[2], pd13[2];
    if (pipe(pd12) < 0) {
        perror("Error opening the pipe12");
        exit(1);
    }
    if (pipe(pd13) < 0) {
        perror("Error openinig the pipe13");
        exit(1);
    }

    if (fork() == 0) {
        close(pd13[0]);
        close(pd13[1]);
        close(pd12[1]);
        int niz[15];
        int c = 0;
        read(pd12[0], niz, 15*sizeof(int));
        for (int i = 0; i < 15; i++)
            if (niz[i] == 0)
                c += 1;
        if (c != 15) {
            FILE* c = fopen("PARNI.txt", "w");
            for(int i = 0; i < 15; i++)
                fprintf(c, "%d ", niz[i]);
            fclose(c);
        }
        close(pd12[0]);
    }
    else if (fork() == 0) {
        close(pd12[0]);
        close(pd12[1]);
        close(pd13[1]);
        int niz[15];
        int c = 0;
        read(pd13[0], niz, 15*sizeof(int));
        for (int i = 0; i < 15; i++)
            if (niz[i] == 0)
                c += 1;
        if (c != 15) {
            for(int i = 0; i < 15; i++)
                printf("%d ", niz[i]);
            printf("\n");
        }
        close(pd13[0]);
    }
    else {
        close(pd12[0]);
        close(pd13[0]);
        int niz[15];
        int nizEnd[15];
        for (int i = 0; i < 15; i++) {
            niz[i] = rand() % 65;
            nizEnd[i] = 0;
        }
        if (niz[0] % 2 == 0) {
            write(pd12[1], niz, 15 * sizeof(int));
            write(pd13[1], nizEnd, 15 * sizeof(int));
        }
        else {
            write(pd12[1], nizEnd, 15 * sizeof(int));
            write(pd13[1], niz, 15 * sizeof(int));
        }
        wait(NULL);
        wait(NULL);
        close(pd12[1]);
        close(pd13[1]);
        return 0;
    }
}