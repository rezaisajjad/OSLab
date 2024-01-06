#include <stdio.h>
int main(int argc, char const *argv[])
{
    int count = 0;
    printf("count: ");
    scanf("%d", &count);
    int times[count + 1];
    times[0] = 0;

    printf("enter running times: ");
    for (size_t i = 1; i <= count; i++)
    {
        scanf("%d", times + i);
        for (size_t j = i; j > 0; j--)
        {
            if (times[j-1] > times[j])
            {
                int temp = times[j-1];
                times[j-1] = times[j];
                times[j] = temp;
            }
        }
    }
    for (size_t i = 1; i <= count; i++)
    {
        times[i] += times[i - 1];
    }
    printf("[PID]\tStart Time\tEnd Time\tWaiting Time\trunning Time\n");
    for (size_t i = 1; i <= count; i++)
    {
        printf("[%d]\t%d\t\t%d\t\t%d\t\t%d\n", i, *(times + i - 1), *(times + i), *(times + i - 1), *(times + i) - *(times + i - 1));
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
