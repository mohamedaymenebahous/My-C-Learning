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

    //int sumFromChild1, sumFromChild2;
    //int totalSum1, totalSum2;
    int totalSum1;

    if (id1 == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
        wait(NULL);
    } 
    else if (id2 == 0)
    {
        int sumForChild1;
        close(fd[1]);
        read(fd[0], &sumForChild1, sizeof(sumForChild1));
        close(fd[0]);
        totalSum1 = sum + sumForChild1;

        write(fd[2], &totalSum1, sizeof(totalSum1));
        close(fd[2]);
    }
    else 
    {
        int sumFromChild2;
        close(fd[2]);
        read(fd[0], &sumFromChild2, sizeof(sumFromChild2));
        close(fd[0]);

        int totalSum2 = sum + sumFromChild2;
        printf("Total sum : %d\n", totalSum2);
        wait(NULL);
    }
    
    return 0;
}