#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <wait.h>

#define QUEUE_MSG_KEY 12001

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 22, 1 };

    if (fork() != 0) {
        while (buf.num != 0) {
            printf("Broj: ");
            scanf("%d", &buf.num);
            msgsnd(key, &buf, sizeof(int), 0);
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int s = 0;
        while (buf.num != 0) {
            msgrcv(key, &buf, sizeof(int), 22, 0);
            s += buf.num;
        }
        printf("S=%d\n", s);
    }
}