#include <semaphore.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#define LIMIT 9
#define key_addr "/"
#define key_pid 7080

int main(int argc, char const *argv[])
{
    int seg_size = (2 * sizeof(int) + 1 * sizeof(sem_t));
    key_t key = ftok(key_addr, key_pid);
    int __shmflg = 0;
    int is_reader = 1;
    if (fork())
    {
        fork();
        __shmflg = IPC_CREAT | 0444;
    }
    else
    {
        __shmflg = IPC_CREAT | 0666;
        is_reader = 0;
    }
    int segment_id = shmget(
        key,
        seg_size,
        __shmflg);

    int *shm = (int *)shmat(segment_id, NULL, 0);
    sem_t *semaphor = (sem_t *)(shm + 2 * sizeof(int));

    if (!is_reader)
    {
        sem_init(semaphor, 3, 2);
        *shm = 0;
    }

    if (is_reader)
    {
        while (1)
        {
            sem_wait(semaphor);
            if (*shm >= LIMIT)
            {
                sem_post(semaphor);
                break;
            }
            printf("read {%d}:  %d\n", getpid(), (*shm));
            sem_post(semaphor);
        }
    }
    else
    {
        while (1)
        {
            sem_wait(semaphor);
            sem_wait(semaphor);
            if (*shm >= LIMIT)
            {
                sem_post(semaphor);
                sem_post(semaphor);
                break;
            }
            printf("writer {%d}:  %d\n", getpid(), ++(*shm));
            sem_post(semaphor);
            sem_post(semaphor);
        }
    }
    shmdt(shm);
    return 0;
}