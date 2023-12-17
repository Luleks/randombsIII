#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define size 20

void clear_buf(char buf[20]) {
    for (int i = 0; i < size; i++)
        buf[i] = '\0';
}

int main() {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening pipe");
        exit(1);
    }
    if (fork() != 0) {
        close(pd[0]);
        char fajl[20], rec[20];
        int len;
        clear_buf(fajl);
        clear_buf(rec);
        printf("Unesite put do datoteke: ");
        scanf("%s", fajl);
        len = strlen(fajl);
        write(pd[1], &len, sizeof(int));
        write(pd[1], fajl, len);

        printf("Unesite kljucnu rec: ");
        scanf("%s", rec);
        len = strlen(rec);
        write(pd[1], &len, sizeof(int));
        write(pd[1], rec, len);

        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        char fajl[20], rec[20];
        clear_buf(fajl);
        clear_buf(rec);
        int len;
        read(pd[0], &len, sizeof(int));
        read(pd[0], fajl, len);
        read(pd[0], &len, sizeof(int));
        read(pd[0], rec, len);

        FILE* f = fopen(fajl, "r");
        len = 1;
        while(!feof(f)) {
            fgets(fajl, 19, f);
            fajl[strcspn(fajl, "\n")] = '\0';
            if (strcmp(rec, fajl) == 0)
                printf("%d\n", len);
            len += 1;
            clear_buf(fajl);
        }
        close(pd[0]);
        fclose(f);
    }
}