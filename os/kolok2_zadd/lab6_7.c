#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void search_dir(char* dirname) {
    DIR* dp = opendir(dirname);
    struct dirent* info;
    struct stat stats;
    char addr[512];

    while ((info = readdir(dp)) != 0) {
        strcpy(addr, dirname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);

        if (S_ISREG(stats.st_mode) && strstr(info->d_name, ".sh") != NULL) {
            if (fork()) {
                execlp("sh", "sh", addr, NULL);
            }
            else
                wait(NULL);
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0) {
            search_dir(addr);
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);
}