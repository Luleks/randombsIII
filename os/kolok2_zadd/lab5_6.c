#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define QUEUE_MSG_KEY 10141

struct msg {
    char linija[50];
    int linija_rbr;
    int velika_slova;
};

struct msgbuf {
    long mtype;
    struct msg msg;
};

int main(int argc, char* argv[]) {
    int msg_key = msgget(QUEUE_MSG_KEY, 0666 | IPC_CREAT);
    struct msgbuf buf;
    strcpy(buf.msg.linija, "");

    if (fork() != 0) {
        FILE* f = fopen("primer.txt", "r");
        while (!feof(f)) {
            fgets(buf.msg.linija, 50, f);
            buf.mtype = 1;
            msgsnd(msg_key, &buf, sizeof(struct msg), 0);
            msgrcv(msg_key, &buf, sizeof(struct msg), 2, 0);
            printf("Linija: %d ima %d velikih slova\n", buf.msg.linija_rbr, buf.msg.velika_slova);
        }
        printf("KRAJ\n");
        strcpy(buf.msg.linija, "KRAJ");
        buf.mtype = 1;
        msgsnd(msg_key, &buf, sizeof(struct msg), 0);
        wait(NULL);
        msgctl(msg_key, IPC_RMID, NULL);
        fclose(f);
    }
    else {
        int l_rbr = 1;
        while (1) {
            msgrcv(msg_key, &buf, sizeof(struct msg), 1, 0);
            if (strcmp(buf.msg.linija, "KRAJ") == 0)
                break;
            buf.msg.velika_slova = 0;
            buf.msg.linija_rbr = l_rbr;
            for (int i = 0; i < strlen(buf.msg.linija); i++)
                if ('A' <= buf.msg.linija[i] && buf.msg.linija[i] <= 'Z')
                    buf.msg.velika_slova += 1;
            buf.mtype = 2;
            msgsnd(msg_key, &buf, sizeof(struct msg), 0);
        }
    }
}