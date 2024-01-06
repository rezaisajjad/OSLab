#include <stdio.h>
int main(int argc, char const *argv[])
{
    int count = 0;
    printf("count: ");
    scanf("%d", &count);
    int times[count + 1];
    int priorities[count + 1];
    times[0] = 0;
    priorities[0] = 0;

    printf("enter running times and priorities: ");
    for (size_t i = 1; i <= count; i++)
    {
        scanf("%d %d", times + i, priorities + i);
        for (size_t j = i; j > 1; j--)
        {
            if (priorities[j - 1] < priorities[j])
            {
                int temp = times[j - 1];
                times[j - 1] = times[j];
                times[j] = temp;
                temp = priorities[j - 1];
                priorities[j - 1] = priorities[j];
                priorities[j] = temp;
            }
        }
    }
    for (size_t i = 1; i <= count; i++)
    {
        times[i] += times[i - 1];
    }
    printf("[PID]\tStart Time\tEnd Time\tWaiting Time\trunning Time\tpriority\n");
    for (size_t i = 1; i <= count; i++)
    {
        printf("[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, *(times + i - 1), *(times + i), *(times + i - 1), *(times + i) - *(times + i - 1),*(priorities+i));
    }
    double avg = 0;
    for (size_t i = 0; i < count; i++)
    {
        avg += times[i];
    }
    avg /= count;
    printf("average waiting time: %.3lf", avg);
    return 0;
}
