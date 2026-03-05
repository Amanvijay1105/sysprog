#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: ./gpipe cmd1 cmd2\n");
        return 1;
    }

    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();

    if (pid1 == 0) {

        dup2(pipefd[1], 1);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp(argv[1], argv[1], NULL);
        perror("exec1 failed");
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {

        dup2(pipefd[0], 0);

        close(pipefd[1]);
        close(pipefd[0]);

        execlp(argv[2], argv[2], NULL);
        perror("exec2 failed");
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}