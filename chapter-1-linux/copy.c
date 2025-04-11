#include "myinclude.h"
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    int res;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("Error reading");
        return 1;
    }

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        printf("Error opening read file");
        return 1;
    }
    numRead = read(inputFd, buf, 16);
    if (numRead == -1) {
        printf("Error reading file");
        return 1;
    }
    res = close(inputFd);
    if (res == -1) {
        printf("Error closing read file");
        return 1;
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; 
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        printf("Error opening write file");
        return 1;
    }
    res = write(outputFd, buf, numRead);
    if (res == -1) {
        printf("Failed to write to output file");
        return 1;
    }
    res = close(outputFd);
    if (res == -1) {
        printf("Error closing write file");
        return 1;
    }
    printf("Copied");
    
    res = close(inputFd);
    return 0;
}
