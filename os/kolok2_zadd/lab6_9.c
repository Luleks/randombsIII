#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

struct fajl {
    char put[512];
    int size;
};

struct fajl fajls[100];
int c = 0;

void search_dir(char* dirname) {
    DIR* dp = opendir(dirname);
    struct dirent* info;
    struct stat stats;
    char addr[512];

    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, dirname);
        strcat(addr, "/");
        strcat(addr, info->d_name);
        stat(addr, &stats);

        if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0)
            search_dir(addr);
        else if (S_ISREG(stats.st_mode) && stats.st_size > 100 * 1024) {
            strcpy(fajls[c].put, addr);
            fajls[c++].size = stats.st_size;
        }
    }

    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);

    for (int i = 1; i < c; i++) {
        int j = i - 1;
        struct fajl temp = fajls[i];
        while (j >= 0 && temp.size < fajls[j].size) {
            fajls[j + 1] = fajls[j];
            j -= 1;
        }
        fajls[j + 1] = temp;
    }

    for (int i = 0; i < c; i++) {
        printf("%s || %dB\n", fajls[i].put, fajls[i].size);
    }
} 