#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//uncomment each experiment and debug and run to see results

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0)
    {
        sleep(1);
    }
    printf("Current process id : %d, Parent process id : %d\n", 
        getpid(), getppid());

    /*
    if (id != 0)
    {
        wait(NULL);
    }
    */
    //or simply
    //wait(NULL);

    int res = wait(NULL);
    if (res == -1)
    {
        printf("No children to wait for\n");
    }
    else
    {
        printf("Process %d finished executing\n", res);
    }

    return 0;
}