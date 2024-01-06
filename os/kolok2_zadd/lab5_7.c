#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int c = 0;
int z = 0;

void ctrl_c_handler() {
    c += 1;
    if (c == 4)
        signal(SIGINT, SIG_DFL);
}

void ctrl_z_handler() {
    z += 1;
    if (z == 2) {
        printf("\nCTRL+C clicked %d times\n", c);
        z = 0;
    }
}

int main() {
    signal(SIGINT, ctrl_c_handler);
    signal(SIGTSTP, ctrl_z_handler);
    while (1)
        pause(); 
}