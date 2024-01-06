#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void alarm_handler() {
    printf("\nIsteklo je vreme za unosenje passworda\n");
    exit(1);
}

int main() {
    char username[255];
    char password[255];
    signal(SIGALRM, alarm_handler);
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    alarm(10);
    scanf("%s", password);
    signal(SIGALRM, SIG_DFL);

    printf("Username %s\nPassword %s\n", username, password);
}