#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        printf("Child: fork() returned %d, getpid() is %d\n", pid, getpid());
    } else if (pid > 0) {
        printf("Parent: fork() returned %d, getpid() is %d\n", pid, getpid());
    } else {
        perror("fork failed");
    }

    return 0;
}