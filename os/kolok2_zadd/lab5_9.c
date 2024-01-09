#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define QUEUE_MSG_KEY 16789

struct msgbuf {
    long mtype;
    char poruka[50];
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    buf.mtype = 1;
    strcpy(buf.poruka, "");
    if (fork() != 0) {
        printf("Poruka: ");
        fflush(stdout);
        fgets(buf.poruka, 50, stdin);
        while(strcmp(buf.poruka, "KRAJ\n") != 0) {
            msgsnd(key, &buf, strlen(buf.poruka) + 1, 0);
            printf("Poruka: ");
            fflush(stdout);
            fgets(buf.poruka, 50, stdin);
        }
        msgsnd(key, &buf, strlen(buf.poruka) + 1, 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        FILE* f = fopen("izlaz.txt", "w");
        msgrcv(key, &buf, 50, 1, 0);
        while (strcmp(buf.poruka, "KRAJ\n") != 0) {
            fputs(buf.poruka, f);
            msgrcv(key, &buf, 50, 1, 0);
        }
        fclose(f);
    }
}