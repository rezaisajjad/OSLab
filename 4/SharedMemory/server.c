#include "shared.h"
int main(int argc, char const *argv[])
{
    key_t key = ftok(key_addr, key_pid);
    int segment_id = shmget(
        key,
        seg_size,
        IPC_CREAT | 0666);
    char *shared_memory = shmat(segment_id, NULL, 0);

    int *counter = shared_memory;
    *counter = 0;

    shared_memory += 4;
    *shared_memory = 0;

    char *text = calloc(512, sizeof(char));

    while (1)
    {
        scanLine(text);
        strcat(text, "\n");
        strcpy((shared_memory + *counter), text);
        (*counter) += strlen(text);
    }

    shmdt(shared_memory);
    return 0;
}
