#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
    //1st experiment
    //int id = fork();
    //printf("Hello world from %d\n", id);

    //2nd experiment
    /*
    if (id == 0) 
    {
        printf("Hello from the child process\n");
    }
    else
    {
        printf("Hello from the main process\n");
    }
    */

    //3rd experiment
    /*
    fork();
    fork(); 
    printf("Hello World\n");
    */

    return 0;
}