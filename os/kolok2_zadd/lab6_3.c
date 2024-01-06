#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>

struct info {
    char put[512];
    int size;
};

struct info fajls[100];
int c = 0;

bool has_digit(char* string) {
    int i = 0;
    while (string[i] != '\0') {
        if ('0' <= string[i] && string[i] <= '9')
            return true;
        i += 1;
    }
    return false;
}

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
        if (S_ISREG(stats.st_mode) && has_digit(info->d_name)) {
            strcpy(fajls[c].put, addr);
            fajls[c++].size = stats.st_size;
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0)
            search_dir(addr);
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);
    for (int i = 1; i < c; i++) {
        int j = i - 1;
        struct info temp = fajls[i];
        while (j >= 0 && fajls[j].size < temp.size) {
            fajls[j + 1] = fajls[j];
            j -= 1;
        }
        fajls[j + 1] = temp;
    }
    for (int i = 0; i < c; i++) {
        printf("%s || %dB\n", fajls[i].put, fajls[i].size);
    }
}