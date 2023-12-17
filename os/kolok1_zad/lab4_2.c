#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

int main() {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening the pipe");
        return 0;
    }
    if (fork() != 0) {
        close(pd[0]);
        int N;
        printf("N: ");
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int randy = rand() % 44;
            write(pd[1], &randy, sizeof(int));
        }
        N = -1;
        write(pd[1], &N, sizeof(int));
        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        int recv;
        FILE* f = fopen("tmp.txt", "w");
        read(pd[0], &recv, sizeof(int));
        while (recv != -1) {
            fprintf(f, "%d\n", recv);
            read(pd[0], &recv, sizeof(int));
        }
        fclose(f);
        close(pd[0]);
    }
}