#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define MAIN_SEM_KEY 10505
#define SEM1_KEY 10502
#define SEM2_KEY 10503
#define SHM_KEY 11404
#define SIZE 80

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo * __buf;
    void * __pad;
};

int main() {
    int main_sem = semget(MAIN_SEM_KEY, 1, 0666 | IPC_CREAT);
    int sem1_key = semget(SEM1_KEY, 1, 0666 | IPC_CREAT);
    int sem2_key = semget(SEM2_KEY, 1, 0666 | IPC_CREAT);
    int shm_key = shmget(SHM_KEY, SIZE, 0666 | IPC_CREAT);
    union semun opts;

    opts.val = 1;
    semctl(sem1_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem2_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(main_sem, 0, SETVAL, opts);

    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0 };

    if (fork() == 0) {
        FILE* f = fopen("ulaz1.txt", "r");
        char* buf = shmat(shm_key, NULL, 0);
        while (!feof(f)) {
            semop(sem1_key, &lock, 1);
            fgets(buf, SIZE, f);
            semop(main_sem, &unlock, 1);
        }
        semop(sem1_key, &lock, 1);
        strcpy(buf, "KRAJ");
        semop(main_sem, &unlock, 1);
        fclose(f);
        shmdt(buf);        
    }
    else if (fork() == 0) {
        FILE* f = fopen("ulaz2.txt", "r");
        char* buf = shmat(shm_key, NULL, 0);
        while (!feof(f)) {
            semop(sem2_key, &lock, 1);
            fgets(buf, SIZE, f);
            semop(main_sem, &unlock, 1);
        }
        semop(sem2_key, &lock, 1);
        strcpy(buf, "KRAJ");
        semop(main_sem, &unlock, 1);
        fclose(f);
        shmdt(buf);   
    }
    else {
        char* buf = shmat(shm_key, NULL, 0);
        FILE* f = fopen("res.txt", "w");
        int done = 0;
        while (done != 2) {
            semop(main_sem, &lock, 1);
            if (strcmp(buf, "KRAJ") == 0)
                done += 1;
            fputs(buf, f);
            semop(sem2_key, &unlock, 1);
            semop(main_sem, &lock, 1);
            if (strcmp(buf, "KRAJ") == 0)
                done += 1;
            fputs(buf, f);
            semop(sem1_key, &unlock, 1);
        }
        wait(NULL);
        wait(NULL);
        fclose(f);
        semctl(sem1_key, 0, IPC_RMID, 0);
        semctl(sem2_key, 0, IPC_RMID, 0);
        semctl(main_sem, 0, IPC_RMID, 0);
        shmctl(shm_key, IPC_RMID, NULL);
    }
}