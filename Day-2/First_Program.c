#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//uncomment each experiment and debug and run to see results
 
int main(int argc, char *argv[])
{
    int fd[2]; //filde descriptors
    //fd[0] for reading
    //fd[1] for writing
    if (pipe(fd) == -1)
    {
        printf("An error occurred with opening the pipe\n");
        return 1;
    }
    int id = fork();
    if (id == -1)
    {
        printf("An error occurred with fork\n");
        return 2;
    }
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("An error occurred with writing to the pipe\n");
            return 3;
        }
        close(fd[1]);
    }
    else 
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("An error occurred with reading from the pipe\n");
            return 4;
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}