#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSG_QUEUE_KEY 12002

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    buf.mtype = 3;
    buf.num = 0;

    if (fork() != 0) {
        while (buf.num != 787) {
            printf("Num > 0: ");
            scanf("%d", &buf.num);
            msgsnd(key, &buf, sizeof(int), 0);
        }
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        FILE* f = fopen("file.txt", "w");
        while (buf.num != 787) {
            msgrcv(key, &buf, sizeof(int), 3, 0);
            fprintf(f, "%d\n", buf.num);
        }
        fclose(f);
    }
}