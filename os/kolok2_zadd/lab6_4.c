#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define SEM1_KEY 10005
#define SEM2_KEY 10006
#define SEM3_KEY 10007
#define SHM_KEY 10008
#define SHM_RUN 10009

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
    int sem3_key = semget(SEM3_KEY, 1, 0666 | IPC_CREAT);
    int shm_key = shmget(SHM_KEY, 50, 0666 | IPC_CREAT);
    int run_key = shmget(SHM_RUN, 2 * sizeof(bool), 0666 | IPC_CREAT);
    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0 };
    union semun opts;

    opts.val = 0;
    semctl(sem1_key, 0, SETVAL, opts);
    opts.val = 1;
    semctl(sem2_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem3_key, 0, SETVAL, opts);

    bool* run = shmat(run_key, NULL, 0);
    run[1] = true;
    run[2] = true;
    shmdt(run);

    if (fork() == 0) {
        char* buf = shmat(shm_key, NULL, 0);
        bool* run = shmat(run_key, NULL, 0);
        FILE* f = fopen("ulaz1.txt", "r");
        while (!feof(f)) {
            semop(sem2_key, &lock, 1);
            fgets(buf, 50, f);
            semop(sem1_key, &unlock, 1);
        }
        semop(sem2_key, &lock, 1);
        run[1] = false;
        printf("CHILD1 %d %d\n", run[1], run[2]);
        semop(sem3_key, &unlock, 1);
        shmdt(buf);
        shmdt(run);
        fclose(f);
    }
    else if (fork() == 0) {
        char* buf = shmat(shm_key, NULL, 0);
        bool* run = shmat(run_key, NULL, 0);
        FILE* f = fopen("ulaz2.txt", "r");
        while (!feof(f)) {
            semop(sem3_key, &lock, 1);
            fgets(buf, 50, f);
            semop(sem1_key, &unlock, 1);
        }
        semop(sem3_key, &lock, 1);
        run[2] = false;
        printf("CHILD2 %d %d\n", run[1], run[2]);
        semop(sem1_key, &unlock, 1);
        shmdt(buf);
        shmdt(run);
        fclose(f);
    }
    else {
        char* buf = shmat(shm_key, NULL, 0);
        char* run = shmat(run_key, NULL, 0);
        FILE* f = fopen("izlaz.txt", "w");
        int i = 0;
        while (1) {
            semop(sem1_key, &lock, 1);
            printf("%d %d\n", run[1], run[2]);
            if (!run[1] && !run[2])
                break;
            fputs(buf, f);
            i += 1;
            if (i % 2 == 1)
                semop(sem3_key, &unlock, 1);
            else
                semop(sem2_key, &unlock, 1);
        }
        wait(NULL);
        wait(NULL);
        shmdt(buf);
        shmdt(run);
        shmctl(shm_key, IPC_RMID, NULL);
        shmctl(run_key, IPC_RMID, NULL);
        semctl(sem1_key, 0, IPC_RMID, 0);
        semctl(sem2_key, 0, IPC_RMID, 0);
        semctl(sem3_key, 0, IPC_RMID, 0);
        fclose(f);
    }

}