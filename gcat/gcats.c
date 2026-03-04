#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        write(2, "Usage: ./gcat <file1> <file2> ...\n", 35);
        return 1;
    }
    char buffer[1024];
    ssize_t bytes;
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);

        if (fd == -1)
        {
            perror("oen");
            continue;
        }
        while ((bytes = read(fd, buffer, sizeof(buffer) > 0)))
        {
            write(1, buffer, bytes);
        }
        close(fd);
    }
    return 0;
}