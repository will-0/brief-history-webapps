#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define STRBUFLEN 64
#define TEXTLEN 13

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Parent: received SIGUSR1!\n");
    }
}

int main(void)
{
    // 1) Create two processes.
    // 2) Iteratively send text across whenever something new is inputted.
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
    int parent_pid = getpid();
    signal(SIGUSR1, handle_signal);

    // Fork
    switch (fork())
    {
    case -1:
        // Error
        printf("Error forking");
        break;
    case 0:
        // Child process
        printf("Child process\n");
        if (close(write_end) == -1) {
            return 1;
        }
        char ch;
        while (read(read_end, &ch, 1) > 0) {
            putchar(ch);
            fflush(stdout);
        }
        ch = '\n';
        putchar(ch);
        fflush(stdout);
        kill(parent_pid, SIGUSR1);
        break;
    default:
        // Parent process
        printf("Parent process\n");
        if (close(read_end) == -1) {
            return 1;
        }
        char my_send_text[TEXTLEN] = "Hello world!";
        for (int i = 0; i < TEXTLEN; i++) {
            write(write_end, &my_send_text[i], 1);
        }
        if (close(write_end) == -1) {
            printf("Unable to close\n");
        }
        sleep(5);
    }
}