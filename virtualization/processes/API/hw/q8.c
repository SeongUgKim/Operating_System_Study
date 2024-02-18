#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t rc[2];
    rc[0] = fork();
    if (rc[0] < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (rc[0] == 0)
    {
        close(pipefd[0]);
        if (pipefd[1] != STDOUT_FILENO)
        {
            if (dup2(pipefd[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                perror("dup");
                exit(EXIT_FAILURE);
            }
            close(pipefd[1]);
        }
        printf('First child says hello.');
    }
    else
    {
        rc[1] = fork();
        if (rc[1] < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (rc[1] == 0)
        {
            close(pipefd[1]);
            if (pipefd[0] != STDIN_FILENO)
            {
                if (dup2(pipefd[0], STDIN_FILENO) != STDIN_FILENO)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]);
            }
            char buf[BUFSIZ];
            read(STDIN_FILENO, buf, BUFSIZ);
            printf("Second child print: %s\n", buf);
        }
        else
        {
            if (waitpid(rc[0], NULL, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (waitpid(rc[1], NULL, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}