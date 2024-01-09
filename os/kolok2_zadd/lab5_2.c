#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_QUEUE_KEY 12002

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf = { 3, 0 };
    if (fork() != 0)  {
        printf("Broj: ");
        scanf("%d", &buf.num);
        while (buf.num != 787) {
            msgsnd(key, &buf, sizeof(int), 0);
            printf("Broj: ");
            scanf("%d", &buf.num);
        }
        msgsnd(key, &buf, sizeof(int), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
    else {
        msgrcv(key, &buf, sizeof(int), 3, 0);
        FILE* f = fopen("izlaz.txt", "w");
        while (buf.num != 787) {
            fprintf(f, "%d\n", buf.num);
            msgrcv(key, &buf, sizeof(int), 3, 0);
        }
        fclose(f);
    }
}