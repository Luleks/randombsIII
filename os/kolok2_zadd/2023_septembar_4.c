#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        perror("Neodgovarajuci broj parametara");
        exit(1);
    }
    struct stat stats;
    struct dirent* info;

    if (stat(argv[1], &stats) == -1) {
        perror("Error reading from directory");
        exit(1);
    }
    if (!S_ISDIR(stats.st_mode)) {
        perror("First arg is not folder");
        exit(1);
    }
    DIR* dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("Error opening directory");
        exit(1);
    }
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    char addr[255];
    int c = 0;
    while ((info = readdir(dp)) != NULL) {
        if (c == n)
            break;
        strcpy(addr, argv[1]);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);
        if (S_ISREG(stats.st_mode)) {
            c += 1;
            if (fork() == 0) {
                char arg[10];
                strcpy(arg, "-");
                strcat(arg, argv[3]);
                execlp("head", "head", arg, addr, NULL);
            }
            else {
                wait(NULL);
            }
        }
    }
    closedir(dp);
}