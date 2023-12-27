#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <netdb.h>
typedef struct sockaddr_in soin;
#define __userCount__ 5
#define __threadCount__ 5
#define max_group 10
#define max_client 5
#define max_group_client 5
#define max_thread 5
enum opcode
{
    EndConnection = 0001,
    NameInitializer = 0002,
    SendGroupMessage = 0004,
    JoinGroup = 0010,
    LeaveGroup = 0020
};
struct ConnectionInitializer
{
    int len;
    int id;
    enum opcode opc;
};
typedef struct ConnectionInitializer coin;
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
int createSocket()
{
    int sck_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sck_fd <= 0)
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    return sck_fd;
}
soin *createSoin(int port)
{
    soin *addr = (soin *)calloc(1, sizeof(soin));
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    return addr;
}
unsigned int *createLenVar()
{
    unsigned int *len = (unsigned int *)calloc(1, sizeof(soin));
    *len = sizeof(soin);
    return len;
}
void bindSocket(int sck_fd, soin *addr, int port, const unsigned int *len)
{
    int opt = 1;
    if (setsockopt(sck_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }

    int bnd = bind(sck_fd, (struct sockaddr *)addr, *len);
    if (bnd < 0)
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
}
void listenSocket(int sck_fd, int count)
{
    if (listen(sck_fd, count) == -1)
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
}
int acceptSocket(int sck_fd, soin *addr, const unsigned int *len)
{
    int acc = accept(sck_fd, (struct sockaddr *)addr, (socklen_t *)len);
    if (acc < 0)
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    return acc;
}
void connectSocket(int sck_fd, soin *server, int *len)
{
    if (connect(sck_fd, (struct sockaddr *)server, *len) < 0)
    {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
}
void sendMessage(int sck_fd, enum opcode opc, char *text, int id)
{
    int tlen = strlen(text);
    int slen = sizeof(coin);
    coin *co = calloc(1, slen);
    co->opc = opc;
    co->len = tlen;
    co->id = id;
    write(sck_fd, co, slen);
    write(sck_fd, text, tlen);
    free(co);
}
coin *readCoin(int sck_fd)
{
    coin *co = calloc(1, sizeof(coin));
    receiveDataBlocking(sck_fd, co, sizeof(coin));
    return co;
}
char *readText(int sck_fd, int len)
{
    char *text = calloc(1, len);
    receiveDataBlocking(sck_fd, text, len);
    return text;
}
void receiveDataBlocking(int socket, char *buffer, int targetSize)
{
    int totalBytesReceived = 0;
    while (totalBytesReceived < targetSize)
    {
        int bytesReceived = read(socket, buffer + totalBytesReceived, targetSize - totalBytesReceived);
        if (bytesReceived <= 0)
        {
            //perror("Error receiving data");
            exit(0);
            //return -1;
        }
        totalBytesReceived += bytesReceived;
    }
    //return 0;
}