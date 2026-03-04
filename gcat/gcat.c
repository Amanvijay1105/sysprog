#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(2, "Usage: ./gcat<file>", 21);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer) > 0)))
    {
        write(1, buffer, bytes);
    }

    close(fd);
    return 0;
}