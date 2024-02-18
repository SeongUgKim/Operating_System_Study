#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0)
    {
        char *args[2];
        args[0] = "/bin/ls";
        args[1] = NULL;
        if (execvp(args[0], args) == -1)
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int wc = wait(NULL);
        printf("parent");
    }
}