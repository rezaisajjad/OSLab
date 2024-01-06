#include <stdio.h>
int main(int argc, char const *argv[])
{
    int count = 0, tq = 0;
    printf("count: ");
    scanf("%d", &count);
    printf("Time quantum: ");
    scanf("%d", &tq);

    int times[count + 1];
    int remains[count + 1];
    int waitings[count + 1];
    times[0] = 0;
    remains[0] = 0;
    waitings[0] = 0;

    printf("enter running times: ");
    for (size_t i = 1; i <= count; i++)
    {
        scanf("%d", times + i);
        remains[i] = times[i];
    }
    printf("[PID]\tStart Time\tEnd Time\trunning Time\ttotal running Time\tremaining Time\n");
    int change = 1;
    int time = 0;
    while (change)
    {
        change = 0;
        for (size_t i = 1; i <= count; i++)
        {
            int _tq = tq;
            if (remains[i] == 0)
            {
                _tq = remains[i];
                printf("\033[0;30m");
            }
            else if (remains[i] <= tq)
            {
                _tq = remains[i];
                waitings[i] = (time + _tq) - times[i];
            }
            else
                change = 1;
            remains[i] -= _tq;
            time += _tq;
            int totalRun = times[i] - remains[i];
            printf("[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i, time - _tq, time, _tq, totalRun, remains[i]);
            printf("\033[0;37m");
        }
    }
    printf("------------------------\n");
    printf("[PID]\taverage waiting time:\n");
    double avg = 0;
    for (size_t i = 1; i <= count; i++)
    {
        printf("[%d]\t%d\n", i, waitings[i]);
        avg += waitings[i];
    }
    avg /= count;
    printf("average waiting time: %.3lf", avg);
    return 0;
}
