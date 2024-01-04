#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    DIR* dp = opendir(".");
    if (dp == NULL) {
        perror("Error opening working folder");
        exit(1);
    }
    struct dirent* info;
    struct stat stats;
    char addr[255];
    
    int subfolders = 0, links = 0, regs = 0, empty_regs = 0;

    while ((info = readdir(dp)) != NULL) {
        if (strcmp(info->d_name, ".") == 0 || strcmp(info->d_name, "..") == 0)
            continue;

        strcpy(addr, "./");
        strcat(addr, info->d_name);

        if (stat(addr, &stats) == -1) {
            printf("Error reading file %s\n", addr);
            continue;
        }

        if (S_ISDIR(stats.st_mode))
            subfolders += 1;
        else if (S_ISREG(stats.st_mode) && stats.st_size == 0)
            empty_regs += 1;
        else if (S_ISREG(stats.st_mode) && stats.st_size != 0)
            regs += 1;
        else if (S_ISLNK(stats.st_mode))
            links += 1;
    }
    
    printf("Subfolders: %d\nRegular dats: %d\nEmpty regular dats: %d\nLinks : %d\n", subfolders, regs, empty_regs, links);
    closedir(dp);
}