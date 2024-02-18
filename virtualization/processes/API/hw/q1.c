#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0)
    {
        // fork failed
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("var x value in child process: %d\n", x);
        x = 10;
        printf("var x changed value in child process: %d\n", x);
    }
    else
    {
        int wc = wait(NULL);
        printf("var x value in parent process: %d\n", x);
        x = 20;
        printf("var x changed value in parent process: %d\n", x);
    }
}