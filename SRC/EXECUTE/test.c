#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int i;
    struct stat buf;

    i = stat("../", &buf);
    if (i == -1)
        printf("X\n");
    else
    {
        printf("O\n");
    }
    
}