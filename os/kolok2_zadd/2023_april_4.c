#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

char naziv[512];
int max_size = 0;

void process_dir(char* dirname, int level) {
    if (level == 0)
        return;
    DIR* dp = opendir(dirname);
    struct dirent* info;
    struct stat stats;

    char addr[512];
    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, dirname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);
        if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0) {
            process_dir(addr, level - 1);
        }
        else if (S_ISREG(stats.st_mode) && stats.st_size > max_size) {
            strcpy(naziv, addr);
            max_size = stats.st_size;
        } 
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    process_dir(argv[1], 5);
    printf("Max dat: %s\nSize: %d\n", naziv, max_size);
}