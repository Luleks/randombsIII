#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/sem.h>

#define QUEUE_MSG_KEY 10101
#define SEM1_KEY 10001
#define SEM2_KEY 10002
#define MAX_LEN 50

struct msgbuf {
    long mtype;
    char msg[MAX_LEN];
};

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo * __buf;
    void * __pad;
};

int main() {
    struct sembuf lock = { 0, -1, 0 };
    struct sembuf unlock = { 0, 1, 0};
    union semun opts;
    struct msgbuf buf;
    buf.mtype = 1;
    strcpy(buf.msg, "");

    int msg_key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    int sem1_key = semget(SEM1_KEY, 1, 0666 | IPC_CREAT);
    int sem2_key = semget(SEM2_KEY, 1, 0666 | IPC_CREAT);

    opts.val = 1;
    semctl(sem1_key, 0, SETVAL, opts);
    opts.val = 0;
    semctl(sem2_key, 0, SETVAL, opts);

    if (fork() == 0) {
        FILE* f;
        while (1) {
            msgrcv(msg_key, &buf, MAX_LEN, 1, 0);
            if (strcmp(buf.msg, "ENDE") == 0)
                break;
            for (int i = 0; i < strlen(buf.msg); i++) 
                if ('A' < buf.msg[i] && buf.msg[i] < 'Z')
                    buf.msg[i] = 'a' - 'A' + buf.msg[i];
            semop(sem1_key, &lock, 1);
            f = fopen("sadrzaj.txt", "a");
            fputs(buf.msg, f);
            fclose(f);
            semop(sem2_key, &unlock, 1);
        }
    }
    else if (fork() == 0) {
        FILE* f;
        while (1) {
            msgrcv(msg_key, &buf, MAX_LEN, 2, 0);
            if (strcmp(buf.msg, "ENDE") == 0)
                break;
            for (int i = 0; i < strlen(buf.msg); i++) 
                if ('a' < buf.msg[i] && buf.msg[i] < 'z')
                    buf.msg[i] = 'A' - 'a' + buf.msg[i];
            semop(sem2_key, &lock, 1);
            f = fopen("sadrzaj.txt", "a");
            fputs(buf.msg, f);
            fclose(f);
            semop(sem1_key, &unlock, 1);
        }
    }
    else {
        int c = 1;
        FILE* f = fopen("poruka.txt", "r");
        while (!feof(f)) {
            buf.mtype = c;
            fgets(buf.msg, MAX_LEN, f);
            msgsnd(msg_key, &buf, strlen(buf.msg) + 1, 0);
            c = 3 - c;
        }
        strcpy(buf.msg, "ENDE");
        buf.mtype = 1;
        msgsnd(msg_key, &buf, strlen(buf.msg) + 1, 0);
        buf.mtype = 2;
        msgsnd(msg_key, &buf, strlen(buf.msg) + 1, 0);
        wait(NULL);
        wait(NULL);
        semctl(sem1_key, 0, IPC_RMID, 0);
        semctl(sem2_key, 0, IPC_RMID, 0);
        msgctl(msg_key, IPC_RMID, NULL);
    }
}