// This is meant to be a simple implementation of a shell
#include "myinclude.h"

#define BUF_SIZE 1024
extern char **environ;

int main(void)
{
    char buf[BUF_SIZE];
    ssize_t numRead;
    ssize_t arrayPointer = 0;
    pid_t shell_pid;
    pid_t forked_pid;
    int res;

    shell_pid = getpid();
    printf("Enter the absolute path to a program that provides no arguments");

    while (1)
    {
        if ((numRead = read(STDIN_FILENO, &buf[arrayPointer], 1)) > 0)
        {
            if (buf[arrayPointer] == '\n')
            {
                buf[arrayPointer] = '\0'; // null-terminate the string
                break;
            }
            arrayPointer++;
        }
    }

    forked_pid = fork();
    if (forked_pid == 0) {
        buf[arrayPointer] = '\0';
        char *args[] = {buf, NULL};
        res = execve(buf, args, environ);
        if (res == -1)
        {
            printf("Error forking");
            _exit(1);
        }
    }
    else if (forked_pid > 0)
    {
        return 0;
    }
    else
    {
        printf("Fork failed");
        return 1;
    }
    return 0;
}