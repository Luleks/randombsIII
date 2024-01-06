#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    DIR* dp1 = opendir(argv[1]);
    DIR* dp2 = opendir(argv[2]);

    struct dirent* info1;
    struct dirent* info2;

    struct stat stats1;
    struct stat stats2;

    char addr1[255];
    char addr2[255];

    while ((info1 = readdir(dp1)) != NULL) {
        strcpy(addr1, argv[1]);
        strcat(addr1, "/");
        strcat(addr1, info1->d_name);

        stat(addr1, &stats1);
        
        while ((info2 = readdir(dp2)) != NULL) {
            strcpy(addr2, argv[2]);
            strcat(addr2, "/");
            strcat(addr2, info2->d_name);

            stat(addr2, &stats2);
            if (S_ISREG(stats1.st_mode) && strcmp(info1->d_name, info2->d_name) == 0 && stats1.st_size == stats2.st_size) {
                printf("%s == %s\n", addr1, addr2);
            }
        }

        rewinddir(dp2);
    }
    closedir(dp1);
    closedir(dp2);
}