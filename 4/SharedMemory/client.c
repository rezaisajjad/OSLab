#include "shared.h"
int main(int argc, char const *argv[])
{
    key_t key = ftok(key_addr, key_pid);
    int segment_id = shmget(
        key,
        seg_size,
        0666);
    printf("segmentID= %d\nkey= %d\n", segment_id, key);

    char *shared_memory = shmat(segment_id, NULL, 0);

    int *counter = shared_memory;
    int myCounter = 0;

    shared_memory += 4;

    char *text = calloc(512, sizeof(char));
    
    while (1)
    {
        if (myCounter < *counter)
        {
            strcpy(text,shared_memory + myCounter);
            printf("%s", text);
            myCounter+=strlen(text);
        }else
        {
            sleep(1);
        }
    }

    printf("\n");

    shmdt(shared_memory);
    return 0;
}
