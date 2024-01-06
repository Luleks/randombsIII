#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

struct file {
    char put[512];
    int size;
};

struct file files[100];
int s = 0;

void search_dir(char* pathname) {
    DIR* dp = opendir(pathname);
    struct dirent* info;
    struct stat stats;
    char addr[512];

    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, pathname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);

        if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0)
            search_dir(addr);
        else if (S_ISREG(stats.st_mode) && strchr(info->d_name, 'p') != NULL) {
            int i = s - 1;
            while (i >= 0 && files[i].size > stats.st_size) {
                files[i + 1] = files[i];
                i -= 1;
            }
            files[i + 1].size = stats.st_size;
            strcpy(files[i+1].put, addr);
            s += 1;
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);
    for (int i = 0; i < s; i++) {
        printf("%s || %dB\n", files[i].put, files[i].size);
    }
}