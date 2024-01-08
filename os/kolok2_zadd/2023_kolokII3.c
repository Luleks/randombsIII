#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
    #include <sys/msg.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>

#define MSG_QUEUE_KEY 12345

struct msgbuf {
    long priority;
    int num;
};

int main() {
    srand(time(NULL));
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 1, 0 };

    if (fork() != 0) {
        while (buf.num != -1) {
            buf.num = rand() % 1000;
            buf.priority = (buf.num < 10) ? 1 : ((buf.num < 100) ? 2 : 3);
            msgsnd(key, &buf, sizeof(int), 0);
            if (msgrcv(key, &buf, sizeof(int), 4, IPC_NOWAIT) != -1)
                break;
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int s[3] = { 0, 0, 0 };
        while (s[0] + s[1] + s[2] < 50000) {
            while (msgrcv(key, &buf, sizeof(int), 1, IPC_NOWAIT) != -1) {
                s[0] += buf.num;
            }
            while (msgrcv(key, &buf, sizeof(int), 2, IPC_NOWAIT) != -1) {
                s[1] += buf.num;
            }           
            while (msgrcv(key, &buf, sizeof(int), 3, IPC_NOWAIT) != -1) {
                s[2] += buf.num;
            }
        }
        buf.priority = 4;
        buf.num = -1;
        msgsnd(key, &buf, sizeof(int), 0);
        printf("S0 = %d\nS1 = %d\nS2 = %d\n", s[0], s[1], s[2]);
    }
}