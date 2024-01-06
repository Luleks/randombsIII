#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int c1 = 0;
int pid1;
int c2 = 0;
int pid2;

void sigusr2_handler() {
    int buf[10];
    int file = open("prenos.dat", O_WRONLY | O_TRUNC | O_CREAT);
    for (int j = 0; j < 10; j++)
        buf[j] = 10 + rand() % 50;
    write(file, &buf, 10 * sizeof(int));
    close(file);
    c1 += 1;
    if (c1 == 10)
        signal(SIGUSR2, SIG_DFL);
    kill(pid1, SIGUSR1);
}

void sigusr1_handler() {
    int buf[10];
    int file = open("prenos.dat", O_RDONLY);
    read(file, &buf, 10 * sizeof(int));
    for (int j = 0; j < 10; j++)
        printf("%d ", buf[j]);
    printf("\n");
    close(file);
    c2 += 1;
    if (c2 == 10)
        signal(SIGUSR1, SIG_DFL);
    kill(pid2, SIGUSR2);
}

int main() {
    srand(time(NULL));
    int pid;
    int buf[10];
    if ((pid = fork()) != 0) {
        pid1 = pid;
        signal(SIGUSR2, sigusr2_handler);
        while(1) {
            pause();
            if (c1 == 10)
                break;
        }
        wait(NULL);
    }
    else {
        pid2 = getppid();
        signal(SIGUSR1, sigusr1_handler);
        kill(pid2, SIGUSR2);
        while(1) {
            pause();
            if (c2 == 10)
                break;
        }
    }
}