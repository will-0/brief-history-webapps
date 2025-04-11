#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Child: received SIGUSR1!\n");
    }
}

int main() {
    int pid = fork();

    if (pid == 0) {
        signal(SIGUSR1, handle_signal);
        int seconds_waited = sleep(5);
        printf("Signal waited %d seconds\n", seconds_waited);
    } else if (pid > 0) {
        sleep(1);
        kill(pid, SIGUSR1);
    } else {
        perror("fork failed");
    }

    return 0;
}