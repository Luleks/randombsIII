#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

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

int main() {
    srand(time(0));
    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0};
    union semun opts;
    int mutex_id, sem1_id, sem2_id;
    FILE * f;

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
        for (int i = 0; i < 20; i++) {
            semop(sem1_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            f = fopen("dat.txt", "a");
            for (int j = 0; j < 3; j++)
                fprintf(f, "\n%d ", rand());
            fclose(f);
            semop(mutex_id, &unlock, 1);
            semop(sem2_id, &unlock, 1);
        }
        wait(NULL);
        semctl(mutex_id, 0, IPC_RMID, 0);
        semctl(sem1_id, 0, IPC_RMID, 0);
        semctl(sem2_id, 0, IPC_RMID, 0);
    }
    else {
        for (int i = 0; i < 20; i++) {
            semop(sem2_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            f = fopen("dat.txt", "a");
            for (int j = 0; j < 2; j++)
                fprintf(f, "\n%d ", -rand());
            fclose(f);
            semop(mutex_id, &unlock, 1);
            semop(sem1_id, &unlock, 1);
        }
    }

}