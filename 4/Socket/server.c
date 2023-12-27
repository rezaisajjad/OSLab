#include "shared.h"

typedef struct Group
{
    int id;
    int cl_count;
    void *clients[max_group_client];
} Group;

typedef struct Client
{
    char *name;
    int sck_fd;
} Client;

Group groups[max_group];
int igroups = 0;
Client clients[max_client];
int iclient = 0;
pthread_t threadPool[max_thread];
int ithreadpool = 0;

void handlerSocket(int sck_fd);

int main(int argc, char const *argv[])
{
    pthread_t pt;
    int sck_fd = createSocket();
    soin *addr = createSoin(atoi(argv[1]));
    unsigned int *len = createLenVar();
    bindSocket(sck_fd, addr, atoi(argv[1]), len);
    listenSocket(sck_fd, __userCount__);

    memset(groups, 0, sizeof(Group) * max_group);
    memset(clients, 0, sizeof(Client) * max_client);
    memset(threadPool, 0, sizeof(pthread_t) * max_thread);

    while (1)
    {
        int client = acceptSocket(sck_fd, addr, len);
        pthread_create(&(threadPool[ithreadpool]), NULL, handlerSocket, client);
        ithreadpool++;
    }

    return 0;
}
void endConnection(Client *cli)
{
    for (size_t i = 0; i < max_group; i++)
    {
        for (size_t j = 0; j < groups[i].cl_count; j++)
        {
            if (groups[i].clients[j] == cli)
            {
                groups[i].clients[j] = NULL;
            }
        }
    }
    printf("%s DisConnected\n", cli->name);
    pthread_exit(NULL);
}
void sendMessageGroup(coin *co, Client *cli,char*text)
{
    Group *_gp = groups + co->id;
    int _isFound_ = 0;
    for (size_t i = 0; i < _gp->cl_count; i++)
    {
        Client *_cli = (_gp->clients)[i];
        if (_cli == cli)
        {
            _isFound_ = 1;
            break;
        }
    }
    if (!_isFound_)
    {
        return;
    }
    char _text[100];
    sprintf(_text, "%d::%s %s\n", co->id, cli->name, text);
    for (size_t i = 0; i < _gp->cl_count; i++)
    {
        Client *_cli = (_gp->clients)[i];
        if (_cli != NULL && _cli != cli)
        {
            sendMessage(_cli->sck_fd, SendGroupMessage, _text, co->id);
        }
    }
    // printf("%d::%s %s\n", co->id, cli->name, text);
    printf("%s", _text);
}
int joinGroup(coin *co, Client *cli)
{
    Group *_gp = &(groups[co->id]);
    int _isFound_ = 0;
    for (size_t i = 0; i < _gp->cl_count; i++)
    {
        Client *_cli = (_gp->clients)[i];
        if (_cli == cli)
        {
            _isFound_ = 1;
            break;
        }
    }
    if (_isFound_)
    {
        return;
    }

    _gp->id = co->id;
    _gp->clients[_gp->cl_count] = cli;
    _gp->cl_count++;
    printf("%s join group %d\n", cli->name, co->id);
}
void leaveGroup(coin *co, Client *cli)
{
    Group *_gp = groups + co->id;
    int _isFound_ = 0;
    for (size_t i = 0; i < _gp->cl_count; i++)
    {
        Client *_cli = (_gp->clients)[i];
        if (_cli == cli)
        {
            _isFound_ = 1;
            break;
        }
    }
    if (!_isFound_)
    {
        return;
    }

    for (size_t i = 0; i < _gp->cl_count; i++)
    {
        if (_gp->clients[i] == cli)
        {
            _gp->clients[i] = NULL;
            continue;
        }
    }
    printf("%s left group %d\n", cli->name, co->id);
}
void handlerSocket(int sck_fd)
{
    Client *cli = NULL;
    int icli = 0;
    while (1)
    {
        coin *co = readCoin(sck_fd);
        char *text = readText(sck_fd, co->len);
        switch (co->opc)
        {
        case EndConnection:
            endConnection(cli);
            free(co);
            free(text);
            free(cli->name);
            break;
        case NameInitializer:
        {
            Client _cli;
            _cli.sck_fd = sck_fd;
            _cli.name = text;
            clients[iclient] = _cli;
            cli = &(clients[iclient]);
            icli = iclient;
            iclient++;
            printf("%s connected\n", cli->name);
            free(co);
            break;
        }
        case SendGroupMessage:
            sendMessageGroup(co,cli,text);
            free(co);
            free(text);
            break;
        case JoinGroup:
            joinGroup(co, cli);
            free(co);
            free(text);
            break;
        case LeaveGroup:
            leaveGroup(co, cli);
            free(co);
            free(text);
            break;
        default:
            break;
        }
    }
}
