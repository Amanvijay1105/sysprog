#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./grun <command> [args...]\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        return 1;
    }
    if (pid == 0)
    {
        execvp(argv[1], &argv[1]);
        perror("exec failed");
    }
    else
    {
        wait(NULL);
    }
    return 0;
}