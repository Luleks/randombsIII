#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>


#define MSG_QUEUE_KEY 10500
int key;


struct msgbuf {
    long mtype;
    time_t time;
};

void alarm_handler() {
    struct msgbuf buf;
    buf.mtype = 20;
    time(&buf.time);
    msgsnd(key, &buf, sizeof(time_t), 0);
}

void ctrl_c_handler() {
    sleep(5);
    msgctl(key, IPC_RMID, NULL);
    exit(0);
}

int main() {
    key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    signal(SIGALRM, alarm_handler);
    signal(SIGINT, ctrl_c_handler);
    if (fork() != 0) {
        for (int i = 1; i < 10; i++) {
            alarm(5*i);
        }
        while(1)
            pause();
    }
    else {
        struct msgbuf buf;
        for (int i = 1; i < 10; i++) {
            msgrcv(key, &buf, sizeof(time_t), 20, 0);
            printf("%s\n", ctime(&buf.time));
        }
    }
}