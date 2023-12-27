#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define key_addr "/"
#define key_pid 7075
#define seg_size 64 * sizeof(char)
void scanLine(char *dest)
{
    char c = 0;
    int index = 0;
    scanf("%c", &c);
    if (c == '\n')
        scanf("%c", &c);
    while (c != '\n')
    {
        dest[index] = c;
        index++;
        scanf("%c", &c);
    }
    dest[index] = 0;
}