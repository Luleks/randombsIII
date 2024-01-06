#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>

#define QUEUE_MSG_KEY 12345

struct msgbuf {
    long mtype;
    char chr;
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 4, 'a' };

    if (fork() != 0) {
        while (!('0' <= buf.chr && buf.chr <= '9')) {
            printf("Character: ");
            scanf("%c", &buf.chr);
            msgsnd(key, &buf, sizeof(char), 0);
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        FILE* f = fopen("chars.txt", "w");
        while (1) {
            msgrcv(key, &buf, sizeof(char), 4, 0);
            if ('0' <= buf.chr && buf.chr <= '9')
                break;
            fputc(buf.chr, f);
        }
        fclose(f);
    }
}