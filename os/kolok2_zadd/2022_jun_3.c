#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_MSG_KEY 10101

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 1, 0 };

    if (fork() != 0) {
        for (int i = 0; i < 10; i++) {
            printf("Broj: ");
            scanf("%d", &buf.num);
            msgsnd(key, &buf, sizeof(int), 0);
            msgrcv(key, &buf, sizeof(int), 0, 0);
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        for (int i = 0; i < 10; i++) {
            msgrcv(key, &buf, sizeof(int), 0, 0);
            int s = 0;
            while (buf.num) {
                s += buf.num % 10;
                buf.num /= 10;
            }
            printf("Zbir: %d\n", s);
            msgsnd(key, &buf, sizeof(int), 0);
        }
    }
}