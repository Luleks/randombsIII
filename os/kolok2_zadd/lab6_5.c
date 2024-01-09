#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

#define SEM1_KEY 10101
#define SEM2_KEY 10102
#define SHM_KEY 10103

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo * __buf;
    void * __pad;
};

int main() {
    int sem1_key = semget(SEM1_KEY, 1, 0666 | IPC_CREAT);
    int sem2_key = semget(SEM2_KEY, 1, 0666 | IPC_CREAT);
    int shm_key = shmget(SHM_KEY, 80, 0666 | IPC_CREAT);
    union semun opts;
    struct sembuf lock = { 0, -1, 0};
    struct sembuf unlock = { 0, 1, 0};
    opts.val = 1;
    semctl(sem1_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem2_key, 0, SETVAL, opts);

    if (fork() != 0) {
        FILE* f = fopen("ulaz.txt", "r");
        char* buf = shmat(shm_key, NULL, 0);
        while (!feof(f)) {
            semop(sem1_key, &lock, 1);
            fgets(buf, 80, f);
            semop(sem2_key, &unlock, 1);
        }
        semop(sem1_key, &lock, 1);
        strcpy(buf, "END");
        semop(sem2_key, &unlock, 1);
        wait(NULL);
        shmdt(buf);
        semctl(sem1_key, 0, IPC_RMID, 0);
        semctl(sem2_key, 0, IPC_RMID, 0);   
        shmctl(shm_key, IPC_RMID, NULL);
        fclose(f);    
    }
    else {
        FILE* f = fopen("izlaz.txt", "w");
        char* buf = shmat(shm_key, NULL, 0);
        while (1) {
            semop(sem2_key, &lock, 1);
            if (strcmp(buf, "END") == 0)
                break;
            fputs(buf, f);
            semop(sem1_key, &unlock, 1);
        }
        fclose(f);
        shmdt(buf);
    }
}