#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s old-file new-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        perror("opening input file");
        exit(EXIT_FAILURE);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        perror("opening output file");
        exit(EXIT_FAILURE);
    }

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {

        if (write(outputFd, buf, numRead) != numRead) {
            fprintf(stderr, "couldn't write whole buffer\n");
            exit(EXIT_FAILURE);
        }

    }

    if (numRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (close(inputFd) == -1) {
        perror("close input");
        exit(EXIT_FAILURE);
    }

    if (close(outputFd) == -1) {
        perror("close output");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}