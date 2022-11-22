#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

//uncomment each experiment and debug and run to see results
 
int main(int argc, char *argv[])
{
    int arr[5];
    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {
        arr[i] = rand() % 100; 
        printf("Generated %d\n", arr[i]);
    }

    int fd = open("sum", O_WRONLY);

    if (fd == -1)
    {
        return 1;
    }

    if (write(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }
    
    //alternative method
    /*
    for (int i = 0; i < 5; i++)
    {
        if (write(fd, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }
        printf("Wrote %d\n", arr[i]);
    }*/

    close(fd);

    int fd2 = open("sum", O_RDONLY);
    if (fd2 == -1)
    {
        return 3;
    }

    int sum;

    if (read(fd2, &sum, sizeof(sum)) == -1)
    {
        return 4;
    }

    printf("Received result : %d\n", sum);

    return 0;
}