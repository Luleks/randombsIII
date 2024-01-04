#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>

#define QUEUE_MSG_KEY 10101

struct msgbuf {
    long mtype;
    int br;
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    buf.mtype = 1;
    buf.br = -1;

    if (fork() != 0) {
        printf("Unesite broj 0-127: ");
        scanf("%d", &buf.br);
        while (buf.br != 0) {
            buf.br = buf.br % 128;
            msgsnd(key, &buf, sizeof(int), 0); 
            msgrcv(key, &buf, sizeof(int), 0, 0); 
            printf("Unesite broj 0-127: ");
            scanf("%d", &buf.br);        
        }
        msgsnd(key, &buf, sizeof(int), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        int s = 0;
        while (buf.br != 0) {
            msgrcv(key, &buf, sizeof(int), 0, 0);
            printf("Primljeno %c\n", buf.br);
            s += 1;
            msgsnd(key, &buf, sizeof(int), 0);
        }
        printf("Ukupno primljeno %d poruka\n", s);
    }
}