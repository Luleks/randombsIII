#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>

#define MUTEX_KEY 10001
#define SEM1_KEY 10002
#define SEM2_KEY 10003

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo * __buf;
    void * __pad;
};

void clear_buf(char linija[80]) {
    for (int i = 0; i < 80; i++)
        linija[i] = '\0';
}

int main() {
    int mutex_id, sem1_id, sem2_id;
    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0 };
    union semun opts;

    char linija[80];
    clear_buf(linija);
    FILE* fileC;
    FILE* fileAB;

    mutex_id = semget(MUTEX_KEY, 1, 0666 | IPC_CREAT);
    sem1_id = semget(SEM1_KEY, 1, 0666 | IPC_CREAT);
    sem2_id = semget(SEM2_KEY, 1, 0666 | IPC_CREAT);

    opts.val = 1;
    semctl(mutex_id, 0, SETVAL, opts);
    opts.val = 1;
    semctl(sem1_id, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem2_id, 0, SETVAL, opts);

    if (fork() != 0) {
        fileAB = fopen("prva.txt", "r");
        while(!feof(fileAB)) {
            semop(sem1_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            fileC = fopen("zbir.txt", "a");
            fgets(linija, 80, fileAB);
            fputs(linija, fileC);
            fclose(fileC);
            clear_buf(linija);
            semop(mutex_id, &unlock, 1);
            semop(sem2_id, &unlock, 1);
        }
        wait(NULL);
        semctl(mutex_id, 0, IPC_RMID, 0);
        semctl(sem1_id, 0, IPC_RMID, 0);
        semctl(sem2_id, 0, IPC_RMID, 0);
        return 0;
    }  
    else {
        fileAB = fopen("druga.txt", "r");
        while(!feof(fileAB)) {
            semop(sem2_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            fileC = fopen("zbir.txt", "a");
            fgets(linija, 80, fileAB);
            fputs(linija, fileC);
            fclose(fileC);
            clear_buf(linija);
            semop(mutex_id, &unlock, 1);
            semop(sem1_id, &unlock, 1);
        }
    }
}