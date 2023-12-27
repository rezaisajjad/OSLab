#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

int hist[25] = {0};

int main()
{   
    while (true){
    int sample;
    printf("Enter number of samples: ");
	scanf("%d", &sample);
    if(sample == 0){
        break;
    }
    clock_t t;
    t = clock();
    srand(time(NULL));
    
    if (fork() == 0){
        int counter, random;
        for (int i = 0; i < sample / 2; i++)
        {
            counter = 0;
            for (int j = 0; j < 12; j++)
            {
                random = rand() % 101;
                if (random >= 49)
                {
                    counter++;
                }
                else
                {
                    counter--;
                }
            }
            hist[counter + 12]++;
        }
        exit(0);
    }
    else{
        int counter, random;
        for (int i = 0; i < sample / 2 ; i++)
        {
            counter = 0;
            for (int j = 0; j < 12; j++)
            {
                random = rand() % 101;
                if (random >= 49)
                {
                    counter++;
                }
                else
                {
                    counter--;
                }
            }
            hist[counter + 12]++;
        }
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
    printf("The program took %f seconds to execute\n", time_taken);
    //printNumbers(hist);
    }

    return 0;
}

void printNumbers(int hist[])
{
    for (int i = 0; i < 25; i++)
    {
        printf("%d: %d\n", i - 12, hist[i]);
    }
}

