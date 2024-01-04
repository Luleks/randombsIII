#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <wait.h>

#define QUEUE_MSG_KEY 10101
#define MAX_LEN 50

struct msgbuf {
    long mtype;
    char msg[MAX_LEN];
};

int main() {
    int key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    buf.mtype = 1;
    strcpy(buf.msg, "");

    if (fork() == 0) {
        while (1) {
            msgrcv(key, &buf, MAX_LEN, 1, 0);
            if (strcmp(buf.msg, "END") == 0)
                break;
            printf("%s |%d karaktera\n", buf.msg, strlen(buf.msg));
            msgsnd(key, &buf, strlen(buf.msg) + 1, 0);
        }
    }
    else if (fork() == 0) {
        while (1) {
            msgrcv(key, &buf, MAX_LEN, 2, 0);
            if (strcmp(buf.msg, "END") == 0)
                break;
            for (int i = 0; i < strlen(buf.msg); i++)
                if ('a' <= buf.msg[i] && buf.msg[i] <= 'z')
                    buf.msg[i] = 'A' - 'a' + buf.msg[i];
            printf("%s\n", buf.msg);
            msgsnd(key, &buf, strlen(buf.msg) + 1, 0);
        }        
    }
    else {
        int c;
        printf("Cifra: ");
        scanf("%d", &c);

        while (c == 1 || c == 2) {
            printf("Poruka: ");
            scanf("%s", buf.msg);
            buf.mtype = c;
            msgsnd(key, &buf, strlen(buf.msg) + 1, 0);
            msgrcv(key, &buf, MAX_LEN, 0, 0);
            printf("Cifra: ");
            scanf("%d", &c);
        }
        strcpy(buf.msg, "END");
        buf.mtype = 1;
        msgsnd(key, &buf, strlen(buf.msg) + 1, 0);
        buf.mtype = 2;
        msgsnd(key, &buf, strlen(buf.msg) + 1, 0);
        wait(NULL);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
    }
}