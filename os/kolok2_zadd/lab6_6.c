#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

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
    int shm_key = shmget(SHM_KEY, 2 * sizeof(int), 0666 | IPC_CREAT);
    union semun opts;
    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0};

    opts.val = 1;
    semctl(sem1_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem2_key, 0, SETVAL, opts);

    if (fork() != 0) {
        int* buf = (int*)shmat(shm_key, NULL, 0);
        char input[5];
        while (1) {
            semop(sem1_key, &lock, 1);
            printf("Broj[-999, 9999]/KRAJ: ");
            scanf("%s", input);
            if (strcmp(input, "KRAJ") == 0)
                break;
            buf[0] = atoi(input);
            buf[1] = 3 * buf[0];
            semop(sem2_key, &unlock, 1);
        }
        buf[0] = 10000;
        buf[1] = 10000;
        semop(sem2_key, &unlock, 1);
        wait(NULL);
        shmdt(buf);
        semctl(sem1_key, 0, IPC_RMID, 0);
        semctl(sem2_key, 0, IPC_RMID, 0);
        shmctl(shm_key, IPC_RMID, NULL);
    }
    else {
        int* buf = (int*)shmat(shm_key, NULL, 0);
        while (1) {
            semop(sem2_key, &lock, 1);
            if (buf[0] == 10000 && buf[1] == 10000)
                break;
            printf("%d %d\n", buf[0], buf[1]);
            semop(sem1_key, &unlock, 1);
        }
        shmdt(buf);
    }
}