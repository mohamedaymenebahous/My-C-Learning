#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1) 
    {
        return 1;
    }

    if (pid == 0)
    {
        //Child process
        //execlp("ping", "ping", "-c", "3", "google.com", NULL);
        execlp("mkfifo", "mkfifo", "fifo_test_from_2nd_prog", NULL);
    }
    else
    {
        //Parent process
        wait(NULL);
        printf("Success!\n");
        printf("Post process here\n");
    }

    return 0;
}