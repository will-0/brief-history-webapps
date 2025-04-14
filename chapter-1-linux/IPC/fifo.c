#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define MESSAGE_LENGTH 16
#define FIFO_NAME "/home/willh/temp/example_fifo"

int start_server(void);
int start_client(void);

// TASK
// - Create a FIFO server
// - Create some child process, where they randomly send fixed-length messages to the FIFO server.
// - Print the responses of the
int main(int argc, char *argv[])
{
    // Create FIFO
    if (mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR | S_IWGRP) == -1)
    {
        printf("Unable to make FIFO: %d", errno);
        return -1;
    }

    // Create some clients
    if (start_client() == -1)
    {
        return -1;
    }

    if (start_server() == -1)
    {
        return -1;
    }

    sleep(10);

    return 0;

    // Start listening to the server
}

int start_server(void)
{
    switch (fork())
    {
    case 0:
        int fd;
        printf("Server started\n");
        if (fd = open(FIFO_NAME, O_RDONLY) == -1)
        {
            printf("Server failed to open FIFO, exiting...\n");
            return -1;
        }
        sleep(5);
        if (close(fd) == -1)
        {
            printf("Server failed to close FIFO, exiting...\n");
            return -1;
        }
        printf("Server exiting\n");
        return 0;
    case -1:
        return -1;
    default:
        return 0;
    }
}

int start_client(void)
{
    switch (fork())
    {
    case 0:
        printf("Client started\n");
        int fd;
        if (fd = open(FIFO_NAME, O_WRONLY) == -1)
        {
            printf("Client failed to open FIFO, exiting...\n");
            return -1;
        }
        sleep(5);
        if (close(fd) == -1)
        {
            printf("Client failed to close FIFO, exiting...\n");
            return -1;
        }
        printf("Client exiting\n");
        return 0;
    case -1:
        return -1;
    default:
        return 0;
    }
}