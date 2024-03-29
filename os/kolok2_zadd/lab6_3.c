#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

bool has_digit(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if ('0' <= str[i] && str[i] <= '9')
            return true;
    }
    return false;
}

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

        if (S_ISREG(stats.st_mode) && has_digit(info->d_name)) {
            struct fajl ent;
            strcpy(ent.put, addr);
            ent.size = stats.st_size;
            fajls[c++] = ent;
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0)
            search_dir(addr);
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);

    for (int i = 1; i < c; i++) {
        struct fajl tmp = fajls[i];
        int j = i - 1;
        while (j >= 0 && tmp.size < fajls[j].size) {
            fajls[j + 1] = fajls[j];
            j -= 1;
        }
        fajls[j + 1] = tmp;
    }

    for (int i = 0; i < c; i++)
        printf("%s || %d\n", fajls[i].put, fajls[i].size);
}