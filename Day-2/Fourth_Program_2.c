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
    int fd = open("sum", O_RDONLY);

    if (fd == -1)
    {
        return 1;
    }

    if (read(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }

    //alternative method
    /*
    for (int i = 0; i < 5; i++)
    {
        if (read(fd, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }
        printf("Received %d\n", arr[i]);
    }
    */

    close(fd);

    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += arr[i];
    }
    printf("Result of the sum : %d\n", sum);

    int fd2 = open("sum", O_WRONLY);
    if (fd2 == -1)
    {
        return 3;
    }

    if (write(fd2, &sum, sizeof(sum)) == -1)
    {
        return 4;
    }

    close(fd2);

    return 0;
}