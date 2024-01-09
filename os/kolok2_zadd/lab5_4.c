#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <time.h>

void alrm_handler() {
    printf("\nIsteklo je vreme za upis sifre\n");
    exit(1);
}


int main() {
    signal(SIGALRM, alrm_handler);
    char username[30];
    char password[30];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    alarm(10);
    scanf("%s", password);
    alarm(0);
    printf("Username: %s\nPassword: %s\n", username, password);
}
