#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

//uncomment each experiment and debug and run to see results
 
int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 1, 2, 5, 6, 3, 5 , 1, 2};
    int arrSize = sizeof(arr) / sizeof(int);
    int id1, id2;
    int start, end;
    int fd[3];

    if (pipe(fd) == -1) 
    {
        return 1;
    }

    id1 = fork();

    if (id1 == 0)
    {
        start = 0;
        end = arrSize / 3;
    }
    else 
    {
        id2 = fork();
        if (id2 == 0)
        {
            start = arrSize / 3;
            end = (2 * arrSize) / 3;
        }
        else 
        {
            start = (2 * arrSize) / 3;
            end = arrSize;
        }
    }

    int sum = 0;
    
    int i;
    for (i = start; i < end; i++)
    {
        sum += arr[i];
    }
    printf("Calculated partial sum : %d\n", sum);

    int sumFromChild1, sumFromChild2;
    int totalSum1, totalSum2;

    if (id1 == 0)
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)))
        {
            return 3;
        }
        close(fd[1]);
    } 
    else if (id2 == 0)
    {  
        close(fd[1]);
        if (read(fd[0], &sumFromChild1, sizeof(sumFromChild1)))
        {
            return 4;
        }
        totalSum1 = sum + sumFromChild1;
        close(fd[0]);
        if (write(fd[2], &totalSum1, sizeof(totalSum1)))
        {
            return 5;
        }
        close(fd[2]);
    }
    else 
    {
        close(fd[2]);
        if(read(fd[2], &sumFromChild2, sizeof(sumFromChild2)))
        {
            return 6;
        }
        close(fd[2]);

        totalSum2 = sum + totalSum1;
        printf("Total sum : %d\n", totalSum2);
        wait(NULL);
    }

    /*
    int arr[] = { 1, 2, 3, 4, 1, 2, 5, 6};
    int arrSize = sizeof(arr) / sizeof(int);
    int start, end;
    int fd[2];

    if (pipe(fd) == -1) 
    {
        return 1;
    }

    int id = fork();
    if (id == -1) 
    {
        return 2;
    }

    if (id == 0)
    {
        start = 0;
        end = arrSize / 2;
    }
    else 
    {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    int i;
    for (i = start; i < end; i++)
    {
        sum += arr[i];
    }

    printf("Calculated partial sum : %d\n", sum);

    if (id == 0)
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)))
        {
            return 3;
        }
        close(fd[1]);
    }
    else
    {
        int sumFromChild;
        close(fd[1]);
        if (read(fd[0], &sumFromChild, sizeof(sumFromChild)))
        {
            return 4;
        }
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("Total sum : %d\n", totalSum);
        wait(NULL);
    }
    */

    return 0;
}