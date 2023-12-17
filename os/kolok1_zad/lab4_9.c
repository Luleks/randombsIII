#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <wait.h>

int main() {
    srand(time(NULL));
    int pd12[2], pd13[2];
    int pid2, pid3;
    if (pipe(pd12) < 0)
        exit(1);
    if (pipe(pd13) < 0)
        exit(1);
    if ((pid2 = fork()) == 0) {
        close(pd13[0]);
        close(pd13[1]);
        close(pd12[1]);
        int niz[20];
        int count = read(pd12[0], niz, 20 * sizeof(int));
        if (count == 0) {
            close(pd12[0]);
            exit(0);
        }
        FILE *f = fopen("BROJEVI.TXT", "w");
        for (int i = 0; i < 20; i++)
            fprintf(f, "%d\n", niz[i]);
        fclose(f);
        close(pd12[0]);
    }
    else if ((pid3 = fork()) == 0) {
        close(pd12[0]);
        close(pd12[1]);
        close(pd13[1]);
        int niz[20];
        int count = read(pd13[0], niz, 20 * sizeof(int));
        if (count == 0) {
            close(pd13[0]);
            exit(0);
        }
        for (int i = 0; i < 20; i++) {
            printf("%d ", niz[i]);
        }
        printf("\n");
        close(pd13[0]);
    }
    else {
        close(pd12[0]);
        close(pd13[0]);
        int niz[20];
        int s = 0;
        for (int i = 0; i < 20; i++) {
            niz[i] = rand() % 51;
            s += niz[i];
        }
        if (s % 2 == 0) {
            close(pd13[1]);
            write(pd12[1], &niz, 20 * sizeof(int));
            waitpid(pid2, &s, 0);
            close(pd12[1]);
        }
        else {
            close(pd12[1]);
            write(pd13[1], &niz, 20 * sizeof(int));
            waitpid(pid3, &s, 0);
            close(pd13[1]);
        }
        return 0;
    }
}