#include "shared.h"
void sckPrinter(int sck_fd);

int main(int argc, char const *argv[])
{
    int sck_fd = createSocket();
    soin *addr = createSoin(atoi(argv[1]));
    unsigned int *len = createLenVar();
    connectSocket(sck_fd, addr, len);

    sendMessage(sck_fd, NameInitializer, argv[2], 0);


    pthread_t *tId = calloc(1,sizeof(pthread_t));
    pthread_create(tId,NULL,sckPrinter,sck_fd);

    char text[1024] = {0};
    int id = 0;
    while (strcmp(text, "quit"))
    {
        scanf("%s", text);
        if (!strcmp(text, "join"))
        {
            scanf("%d", &id);
            text[0] = ' ';
            text[1] = 0;
            sendMessage(sck_fd, JoinGroup, text, id);
        }
        else if (!strcmp(text, "send"))
        {
            scanf("%d", &id);
            scanLine(text);
            sendMessage(sck_fd, SendGroupMessage, text, id);
        }
        else if (!strcmp(text, "leave"))
        {
            scanf("%d", &id);
            text[0] = ' ';
            text[1] = 0;
            sendMessage(sck_fd, LeaveGroup, text, id);
        }
    }
    //// end connection
    sendMessage(sck_fd, EndConnection, text, 0);
    pthread_cancel(tId);
    close(sck_fd);
    free(addr);
    free(len);
    free(tId);
    ////
    return 0;
}
void sckPrinter(int sck_fd)
{
    while (1)
    {
        coin *co = readCoin(sck_fd);
        char *text = readText(sck_fd, co->len);
        printf("%s", text);
        free(co);
        free(text);
    }
}