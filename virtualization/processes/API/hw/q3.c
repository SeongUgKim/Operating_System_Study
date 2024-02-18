#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void wait_with_pipe()
{
    printf("wait with pipe\n");
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0)
    {
        printf("hello\n");
        close(pipefd[0]);
        write(pipefd[1], "c", 1);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        char c;
        read(pipefd[0], &c, 1);
        close(pipefd[0]);
        printf("goodbye\n");
    }
}

int main(int argc, char *argv[])
{
    wait_with_pipe();
    return 0;
}