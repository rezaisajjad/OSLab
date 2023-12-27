
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void toUpper(char *text)
{
    int index = 0;
    while (text[index] != 0)
    {
        if (text[index] >= 'a' && text[index] <= 'z')
        {
            text[index] += ('A' - 'a');
        }
        else if (text[index] >= 'A' && text[index] <= 'Z')
        {
            text[index] += ('a' - 'A');
        }

        index++;
    }
}
int main()
{
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1)
    {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe2) == -1)
    {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    if (fork())
    {
        char text[100];
        int len;
        while (1)
        {
            read(pipe1[0], &len, 4);
            read(pipe1[0], text, len);
            toUpper(text);
            write(pipe2[1], text, len);
        }
    }
    else
    {
        char text[100];
        int len;
        while (1)
        {
            scanf("%s", text);
            len = strlen(text);
            write(pipe1[1], &len, 4);
            write(pipe1[1], text, len);
            read(pipe2[0], text, len);
            printf("%s\n", text);
        }
    }
}
