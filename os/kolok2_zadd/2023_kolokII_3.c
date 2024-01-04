#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <wait.h>
#include <time.h>

#define QUEUE_MSG_KEY 10101

struct msgbuf {
    long priority;
    int num;
};

int main() {
    srand(time(NULL));
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    buf.priority = 1;
    buf.num = 0;

    if (fork() != 0) {
        while (buf.num != -1) {
            buf.num = rand() % 1000;
            buf.priority = (buf.num < 10) ? 1 : ((buf.num < 100) ? 2 : 3);
            msgsnd(key, &buf, sizeof(int), 0);
            msgrcv(key, &buf, sizeof(int), 4, 0); 
        }
        wait (NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int sums[3] = { 0, 0, 0 };
        while(sums[0] + sums[1] + sums[2] < 50000) {
            msgrcv(key, &buf, sizeof(int), 0, 0);
            sums[buf.priority - 1] += buf.num;
            buf.priority = 4;
            buf.num = 0;
            msgsnd(key, &buf, sizeof(int), 0);
        }
        buf.priority = 4;
        buf.num = -1;
        msgsnd(key, &buf, sizeof(int), 0);
        printf("%d %d %d\n", sums[0], sums[1], sums[2]);
    }
}