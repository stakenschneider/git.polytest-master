#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    char mode[] = "0777";
    char buf[100] = "/home/osboxes/Documents/syscall_masha/test";
    int i;
    i = strtol(mode, 0, 8);
    int res = chmod (buf,i);
    printf("chmod result %d \n", res);
    if (res < 0)
    {
        fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                argv[0], buf, mode, errno, strerror(errno));
        exit(1);
    }
    return(0);
}
