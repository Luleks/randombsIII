#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int pid;
    if ((pid = fork()) != 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("Child process exited with status code %d\n", status);
        return 0;
    }
    else {
        if (execlp(argv[1], argv[1], argv[2], NULL) < 0) {
            perror("Error trying to execucte execlp");
            exit(1);
        }
    }
}