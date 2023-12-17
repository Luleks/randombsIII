#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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

int main(int argc, char* argv[]) {
    int mutex_id, sem1_id, sem2_id;
    struct sembuf lock = { 0, -1, 0};
    struct sembuf unlock = { 0, 1, 0};
    union semun opts;
    FILE* f = fopen(argv[1], "w");
    fclose(f);

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
        for (int i = 1; i <= 20; i+=2) {
            semop(sem1_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            f = fopen(argv[1], "a");
            fprintf(f, "%d\n", i);
            fclose(f);
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
        for (int i = 2; i <= 20; i+=2) {
            semop(sem2_id, &lock, 1);
            semop(mutex_id, &lock, 1);
            f = fopen(argv[1], "a");
            fprintf(f, "%d\n", i);
            fclose(f);
            semop(mutex_id, &unlock, 1);
            semop(sem1_id, &unlock, 1);
        }
    }

}