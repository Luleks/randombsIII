#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
    srand(time(NULL));
    int pd12[2], pd13[2];
    if (pipe(pd12) < 0) {
        perror("Error opening the pipe12");
        exit(1);
    }
    if (pipe(pd13) < 0) {
        perror("Error opening the pipe13");
        exit(1);
    }
    if (fork() == 0) {
        close(pd13[0]);
        close(pd13[1]);
        close(pd12[1]);
        char niz[21];
        niz[20] = '\0';
        read(pd12[0], niz, 20);
        if (strcmp(niz, "END") != 0) {
            FILE* file = fopen("charz.txt", "w");
            for (int i = 0; i < 20; i++)
                fprintf(file, "%c", niz[i]);
            fclose(file);
        }
        close(pd12[0]);
    }
    else if (fork() == 0) {
        close(pd12[0]);
        close(pd12[1]);
        close(pd13[1]);
        char niz[21];
        niz[20] = '\0';
        read(pd13[0], niz, 20);
        if (strcmp(niz, "END") != 0) {
            printf("HERE\n");
            for (int i = 0; i < 20; i++) {
                printf("%c", niz[i]);
                fflush(stdout);
            }
        }
        close(pd13[0]);
    }
    else {
        close(pd12[0]);
        close(pd13[0]);
        char niz[20];
        char end[20];
        int s = 0;
        for (int i = 0; i < 20; i++) {
            niz[i] = 65 + rand() % 26;
            end[i] = '\0';
            s += (int)niz[i];
        }
        strcpy(end, "END");
        printf("%d\n", s);
        if (s % 2 == 0) {
            write(pd12[1], niz, 20);
            write(pd13[1], end, 20);
        }
        else {
            write(pd12[1], end, 20);
            write(pd13[1], niz, 20);
        }
        wait(NULL);
        wait(NULL);
        close(pd12[1]);
        close(pd13[1]);
        return 0;
    }
}
