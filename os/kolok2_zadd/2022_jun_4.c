#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

void process_dir(char* dirname, int level) {
    if (level == 0)
        return;
    DIR* dp = opendir(dirname);
    struct dirent* info;
    struct stat stats;
    char addr[255];

    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, dirname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);

        if (S_ISREG(stats.st_mode) && strstr(info->d_name, "log") != NULL && stats.st_size > 15 * 1024) {
            if (fork() == 0) {
                execlp("rm", "rm", addr, NULL);
            }
            else {
                wait(NULL);
            }
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0) {
            process_dir(addr, level - 1);
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    process_dir(argv[1], 3);
}