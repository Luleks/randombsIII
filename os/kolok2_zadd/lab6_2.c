#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

struct fajl {
    char put[512];
    int size;
};

struct fajl min_fajls[5];
int c = 0;

void search_file(char* dirname) {
    DIR* dp = opendir(dirname);
    struct dirent* info;
    struct stat stats;
    char addr[512];
    while ((info = readdir(dp)) != NULL) {
        strcpy(addr, dirname);
        strcat(addr, "/");
        strcat(addr, info->d_name);

        stat(addr, &stats);

        if (S_ISREG(stats.st_mode)) {
            struct fajl ent;
            strcpy(ent.put, addr);
            ent.size = stats.st_size;
            if (c == 5) {
                int i = 0;
                while (i < 5 && min_fajls[i].size < stats.st_size)
                    i += 1;
                if (i != 5) {
                    for (int j = 4; j > i; j--)
                        min_fajls[j] = min_fajls[j - 1];
                    min_fajls[i] = ent;
                }
            }
            else {
                int i = c - 1;
                while (i >= 0 && min_fajls[i].size > stats.st_size) {
                    min_fajls[i + 1] = min_fajls[i];
                    i -= 1;
                }
                c += 1;
                min_fajls[i + 1] = ent;
            }
        }
        else if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0)
            search_file(addr);
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_file(".");
    for (int i = 0; i < c; i++) {
        printf("%s || %dB\n", min_fajls[i].put, min_fajls[i].size);
    }
}