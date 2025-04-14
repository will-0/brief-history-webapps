#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define MESSAGE_LENGTH 16
#define FIFO_NAME "/home/willh/temp/example_fifo"

int start_server(void);
int start_client(int pnum);

// TASK
// - Create a FIFO server
// - Create some child process, where they randomly send fixed-length messages to the FIFO server.
// - Print the responses of the
int main(int argc, char *argv[])
{
    int res;
    if ((res = mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR | S_IWGRP)) == -1)
    {
        if (errno == EEXIST)
        {
            printf("FIFO already exists at %s\n", FIFO_NAME);
        }
        else
        {
            printf("Unable to make FIFO: %d\n", errno);
            return -1;
        }
    }

    if (start_server() == -1)
    {
        return -1;
    }

    for (int i = 0; i < 5; i++)
    {
        if (start_client(i) == -1)
        {
            return -1;
        }
    }

    sleep(6); // This is not a satisfactory approach, some synchronization would be preferred, but OK for now.

    return 0;

    // Start listening to the server
}

int start_server(void)
{
    switch (fork())
    {
    case 0:
        int fd;
        char string_buf[MESSAGE_LENGTH];
        printf("[SERVER] started\n");

        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1)
        {
            printf("[SERVER] Server failed to open FIFO, exiting...\n");
            return -1;
        }
        printf("[SERVER] FIFO opened (read)\n");

        while (read(fd, string_buf, MESSAGE_LENGTH) > 0)
        {
            printf("[SERVER] Message received: %s\n", string_buf);
        }

        if (close(fd) == -1)
        {
            printf("[SERVER] failed to close FIFO, exiting...\n");
            return -1;
        }
        printf("[SERVER] exiting\n");
        _exit(0); // Exit instead of return, to prevent spawning more processes in main
    case -1:
        return -1;
    default:
        return 0;
    }
}

int start_client(int pnum)
{
    switch (fork())
    {
    case 0:
        printf("[CLIENT] started\n");
        int fd;
        srand(pnum);
        sleep(rand() % 4);
        char string_buf[MESSAGE_LENGTH];
        snprintf(string_buf, MESSAGE_LENGTH, "Hi from #%d", pnum);
        if ((fd = open(FIFO_NAME, O_WRONLY)) == -1)
        {
            printf("[CLIENT] failed to open FIFO, exiting...\n");
            return -1;
        }
        printf("[CLIENT] FIFO opened (write)\n");

        printf("[CLIENT] sending '%s'\n", string_buf);
        if (write(fd, string_buf, MESSAGE_LENGTH) == -1)
        {
            printf("[CLIENT] Failed to write to buffer");
            return -1;
        }

        if (close(fd) == -1)
        {
            printf("[CLIENT] failed to close FIFO, exiting...\n");
            return -1;
        }
        printf("[CLIENT] closed\n");
        _exit(0);
    case -1:
        return -1;
    default:
        return 0;
    }
}