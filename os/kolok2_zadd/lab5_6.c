#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MSG_QUEUE_KEY 15555

struct msg {
    char msg[50];
    int rbr;
    int len;
};

struct msgbuf {
    long mtype;
    struct msg msg;
};

int main() {
    int key = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;

    if (fork() != 0) {
        FILE* f = fopen("ulaz.txt", "r");
        while (!feof(f)) {
            fgets(buf.msg.msg, 50, f);
            buf.mtype = 1;
            msgsnd(key, &buf, sizeof(struct msg), 0);
            msgrcv(key, &buf, sizeof(struct msg), 2, 0);
            printf("%d | %d\n", buf.msg.rbr, buf.msg.len);
        }
        strcpy(buf.msg.msg, "END");
        buf.mtype = 1;
        msgsnd(key, &buf, sizeof(struct msg), 0);
        wait(NULL);
        msgctl(key, IPC_RMID, NULL);
        fclose(f);
    }
    else {
        msgrcv(key, &buf, sizeof(struct msg), 1, 0);
        int rbr = 1;
        while (strcmp(buf.msg.msg, "END") != 0) {
            buf.msg.rbr = rbr++;
            buf.msg.len = 0;
            for (int i = 0; i < strlen(buf.msg.msg); i++)
                if('A' <= buf.msg.msg[i] && buf.msg.msg[i] <= 'Z')
                    buf.msg.len += 1;
            buf.mtype = 2;
            msgsnd(key, &buf, sizeof(struct msg), 0);
            msgrcv(key, &buf, sizeof(struct msg), 1, 0);
        }
    }
}