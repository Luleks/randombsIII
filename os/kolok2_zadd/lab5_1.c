#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_QUEUE_KEY 12121

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    srand(time(NULL));
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 1, 0 };
    if (fork() != 0) {
        int N = rand() % 20;
        for (int i = 0; i < N; i++) {
            buf.num = rand() % 255;
            msgsnd(key, &buf, sizeof(int), 0);
        }
        buf.num = -1;
        msgsnd(key, &buf, sizeof(int), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        msgrcv(key, &buf, sizeof(int), 1, 0);
        while (buf.num != -1) {
            printf("%d\n", buf.num);
            msgrcv(key, &buf, sizeof(int), 1, 0);
        }
    }
}