#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

void search_dir(char* pathname, char* filename) {
    DIR* dp = opendir(pathname);

    struct dirent* info;
    struct stat stats;
    char addr[255];

    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, pathname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);

        if (S_ISREG(stats.st_mode) && strcmp(info->d_name, filename) == 0) {
            printf("%s %dB\n", addr, stats.st_size);
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0) {
            search_dir(addr, filename);
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1], argv[2]);
}