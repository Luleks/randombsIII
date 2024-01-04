#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <wait.h>

#define QUEUE_MSG_KEY 10101

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 1, 0 };

    if (fork() != 0) {
        int N = rand() % 15;
        for (int i = 0; i < N; i++) {
            buf.num = rand() % 267;
            printf("%d\n", buf.num);
            msgsnd(key, &buf, sizeof(int), 0);
        }
        buf.num = -1;
        msgsnd(key, &buf, sizeof(int), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int par = 0, nep = 0;
        while (buf.num != -1) {
            msgrcv(key, &buf, sizeof(int), 0, 0);
            if (buf.num % 2 == 0)
                par += 1;
            else
                nep += 1;
        }
        printf("Primljeno %d parnih\nPrimljeno %d neparnih\n", par, nep);
    }
}