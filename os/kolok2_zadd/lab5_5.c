#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSG_QUEUE_KEY 12001

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 22, 0 };
    if (fork() != 0) {
        printf("Broj: ");
        scanf("%d", &buf.num);
        while (buf.num != 0) {
            msgsnd(key, &buf, sizeof(int), 0);
            printf("Broj: ");
            fflush(stdout);
            scanf("%d", &buf.num);
        }
        msgsnd(key, &buf, sizeof(int), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int s = 0;
        msgrcv(key, &buf, sizeof(int), 22, 0);
        while (buf.num != 0) {
            s += buf.num;
            msgrcv(key, &buf, sizeof(int), 22, 0);
        }
        printf("Suma: %d\n", s);
    }
}