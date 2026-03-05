#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    char command[100];

    while (1)
    {

        printf("gshell> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0)
            break;

        pid_t pid = fork();

        if (pid == 0)
        {
            execlp(command, command, NULL);
            perror("exec failed");
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}