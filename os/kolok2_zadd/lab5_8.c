#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MSG_QUEUE_KEY 12010

struct msgbuf {
    long mtype;
    char chr;
};

int main() {
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 4, 'a' };
    if (fork() != 0) {
        while(!('0' <= buf.chr && buf.chr <= '9')) {
            printf("Char: ");
            scanf("%c", &buf.chr);
            msgsnd(key, &buf, sizeof(char), 0);
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }    
    else {
        FILE* f = fopen("karakteri.txt", "w");
        while(!('0' <= buf.chr && buf.chr <= '9')) {
            msgrcv(key, &buf, sizeof(char), 4, 0);
            fputc(buf.chr, f);
        }
    }
}