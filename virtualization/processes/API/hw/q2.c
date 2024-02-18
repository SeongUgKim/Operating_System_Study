#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open("./output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(fd >= 0);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed");
    }
    else if (rc == 0)
    {
        char buffer[20];
        sprintf(buffer, "child\n");
        int c = write(fd, buffer, strlen(buffer));
        assert(c == (strlen(buffer)));
    }
    else
    {
        // int wc = wait(NULL);
        char bufferParent[20];
        sprintf(bufferParent, "parent\n");
        int d = write(fd, bufferParent, strlen(bufferParent));
        assert(d == (strlen(bufferParent)));
    }

    return 0;
}
