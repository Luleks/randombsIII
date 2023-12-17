#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define size 20
#define and &&

void clear_buf(char* buf) {
    for (int i = 0; i < size; i++)
        buf[i] = '\0';
}

int main() {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening them legz heheheh");
        exit(1);
    }
    if (fork() != 0) {
        close(pd[0]);
        char fajl[20];
        int len;
        clear_buf(fajl);

        printf("Fajl/KRAJ: ");
        scanf("%s", fajl);
        while (strcmp(fajl, "KRAJ") != 0) {
            len = strlen(fajl);
            write(pd[1], &len, sizeof(int));
            write(pd[1], fajl, len);

            clear_buf(fajl);
            printf("Fajl/KRAJ: ");
            scanf("%s", fajl);
        }
        len = strlen(fajl);
        write(pd[1], &len, sizeof(int));
        write(pd[1], fajl, len);
        wait(NULL);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        char fajl[20];
        int len;
        clear_buf(fajl);

        read(pd[0], &len, sizeof(int));
        read(pd[0], fajl, len);
        while (strcmp(fajl, "KRAJ") != 0) {
            if ('0' <= fajl[0] and fajl[0] <= '9') {
                if (fork() == 0) {
                    char new_name[20];
                    clear_buf(new_name);
                    strcpy(new_name, fajl);
                    new_name[strlen(new_name)] = 'n';
                    if (execlp("mv", "mv", fajl, new_name, NULL) < 0) {
                        perror("Error with cp\n");
                        exit(1);
                    }        
                }
            }
            clear_buf(fajl);
            read(pd[0], &len, sizeof(int));
            read(pd[0], fajl, len);
        }
    }
}