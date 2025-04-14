#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define STRBUFLEN 64
#define TEXTLEN 13
#define NUM_CHILD_PROCESSES 10

void handle_signal(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Parent: received SIGUSR1!\n");
    }
}

int main(void)
{
    int res;
    int fildescrip[2];

    // Create the pipe
    res = pipe(fildescrip);
    if (res == -1)
    {
        _exit(1);
    }
    int read_end = fildescrip[0];
    int write_end = fildescrip[1];

    for (int i = 0; i < NUM_CHILD_PROCESSES; i++)
    {
        switch (fork())
        {
        case -1:
            // Error
            printf("Error forking");
            break;
        case 0:
            // Child process - sleep a random amount of time, then close the pipe
            if (close(read_end) == -1)
            {
                _exit(1);
            }
            srand(i);
            sleep(rand() % 5);
            printf("Child process %d completed\n", i);
            // Child process
            if (close(write_end) == -1)
            {
                _exit(1);
            }
            return 0;
        default:
            // Parent process
            if (i == 0)
            {
                if (close(write_end) == -1)
                {
                    return 1;
                }
            }
        }
    }

    read(read_end, NULL, 1);
    printf("Parent process completed\n");
    return 0;
}