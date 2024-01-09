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

struct fajl fajls[5];
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
        else if (S_ISREG(stats.st_mode)) {
            struct fajl ent;
            strcpy(ent.put, addr);
            ent.size = stats.st_size;
            if (c == 5) {
                int i = 0;
                while (i < 5 && fajls[i].size > ent.size)
                    i += 1;
                if (i < 5) {
                for (int j = 4; j > i; j--)
                    fajls[j] = fajls[j - 1];
                fajls[i] = ent;
                }
            }
            else {
                int i = c - 1;
                while (i >= 0 && fajls[i].size > ent.size) {
                    fajls[i + 1] = fajls[i];
                    i -= 1;
                }
                c += 1;
                fajls[i + 1] = ent;
            }
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]) {
    search_dir(argv[1]);
    for (int i = 0; i < c; i++)
        printf("%s | %dB\n", fajls[i].put, fajls[i].size);
}