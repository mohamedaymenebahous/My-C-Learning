#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
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
        int file = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);

        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if (err == -1)
        {
            printf("Failed to execute, program not found.\n");
            return 2; //not to be confused with the status code 2
        }
    }
    else
    {
        int ws; //wait status
        //Parent process
        wait(&ws);


        if (WIFEXITED(ws))
        {
            int statusCode = WEXITSTATUS(ws);
            if (statusCode == 0)
            {
                printf("Success!\n");
            }
            else 
            {
                printf("Failure, status code: %d\n", statusCode);
            }
        }

        printf("Post process here\n");
    }

    return 0;
}