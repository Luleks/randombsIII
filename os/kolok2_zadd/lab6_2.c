#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

struct info {
    char put[512];
    int size;
};

struct info min_fajls[5];
int c = 0;

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

        if (S_ISDIR(stats.st_mode) && strcmp(info->d_name, ".") != 0 && strcmp(info->d_name, "..") != 0) {
            search_dir(addr);
        }
        else if (S_ISREG(stats.st_mode)) {
            struct info entry;
            strcpy(entry.put, addr);
            entry.size = stats.st_size;
            if (c != 5) {
                int i = c - 1;
                while (i >= 0 && min_fajls[i].size > stats.st_size) {
                    min_fajls[i + 1] = min_fajls[i];
                    i -= 1;
                }
                min_fajls[i + 1] = entry;
                c += 1;
            }
            else {
                int i = 0;
                while (i < 5 && min_fajls[i].size < stats.st_size)
                    i += 1;
                if (i != 5)
                    min_fajls[i] = entry;
            }
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);
    for(int i = 0; i < c; i++) {
        printf("%s || %d\n", min_fajls[i].put, min_fajls[i].size);
    }
}