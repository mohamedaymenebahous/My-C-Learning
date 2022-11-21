#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

//uncomment each experiment and debug and run to see results
 
int main(int argc, char *argv[])
{
    if (mkfifo("My_First_Fifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file");
            return 1;
        }
    }

    printf("Opening...\n");
    int fd = open("My_First_Fifo", O_RDWR);
    if (fd == -1)
    {
        return 3;
    }
    printf("Opened\n");
    int x = 99;
    if (write(fd, &x, sizeof(x)) == -1)
    {
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}