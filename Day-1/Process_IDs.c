#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

//uncomment each experiment and debug and run to see results

int main(int argc, char *argv[])
{
    int id1 = fork();
    int id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
        {
            printf("We are process y\n");
        }
        else
        {
            printf("We are process x\n");
        }
    }
    else 
    {
        if (id2 == 0)
        {
            printf("We are process z\n");
        }
        else 
        {
            printf("We are the parent process\n");
        }
    }

    //wrong line, for experiment purpose only
    //wait(NULL); 

    //correct way
    while(wait(NULL) != -1 || errno != ECHILD)
    {
        printf("Waited for a child to terminate\n");
    }

    return 0;
}