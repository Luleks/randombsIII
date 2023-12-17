#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define size 200

void clear_buf(char* buf, int len) {
    for (int i = 0; i < len; i++)
        buf[i] = '\0';
}

int main(int argc, char* argv[]) {
    int pd[2];
    if (pipe(pd) < 0) {
        perror("Error opening pipe");
        exit(1);
    }
    if (fork() != 0) {
        close(pd[0]);
        FILE* file = fopen(argv[1], "r");
        char buf[size + 1];
        clear_buf(buf, size + 1);
        while (!feof(file)) {
            fgets(buf, size, file);
            write(pd[1], buf, strlen(buf));
            clear_buf(buf, size + 1);
        }
        wait(NULL);
        fclose(file);
        close(pd[1]);
        return 0;
    }
    else {
        close(pd[1]);
        FILE* file = fopen(argv[2], "w");
        char buf[size];
        char xor = 1 + rand() % 255;
        bool run = true;
        int i;
        while (run) {
            int count = read(pd[0], buf, size);
            if (count < size)
                run = false;
            for (i = 0; i < count; i++) {
                buf[i] ^= xor;
                fputc(buf[i], file);
            }
        }
        fclose(file);
        close(pd[0]);
    }
}