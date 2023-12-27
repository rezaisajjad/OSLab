#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define COUNT 5

typedef pthread_mutex_t pmt;

pmt chopsticks[COUNT];

void *start(void *value)
{
    int id = *((int *)value);
    pmt *chop1 = chopsticks + id;
    pmt *chop2 = chopsticks + ((id + 1) % COUNT);
    printf("philosopher %d  is thinking !! \n", id);
    sleep(rand() % 10);
    while (1)
    {
        int c1 = pthread_mutex_trylock(chop1);
        int c2 = pthread_mutex_trylock(chop2);
        if (!c1 && c2)
            pthread_mutex_unlock(chop1);
        else if (!c2 && c1)
            pthread_mutex_unlock(chop2);
        else
        {
            printf("philosopher %d is eating using chopstick[%d] and chopstick[%d]!!\n", id, id, (id + 1) % COUNT);
            sleep(rand() % 10);
            printf("philosopher %d finished eating !!\n", id);
            pthread_mutex_unlock(chop1);
            pthread_mutex_unlock(chop2);
            break;
        }
    }
}

void main()
{
    pthread_t philosophs[COUNT];
    int id[COUNT];
    for (int i = 0; i < COUNT; i++)
    {
        id[i] = i;
        pthread_mutex_init(chopsticks + i, NULL);
    }
    for (int i = 0; i < COUNT; i++)
        pthread_create(philosophs + i, NULL, start, id + i);
    for (int i = 0; i < COUNT; i++)
        pthread_join(philosophs[i], NULL);
}