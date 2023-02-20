// LONG PHAM
// 200437585
// execution command: gcc ass2_Q4.c -pthread
//                    ./a.out [numbers]

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 3;

int *ptr;
int size;
double average;
int maximum, minimum;

void *getAverage(void *args);
void *getMax(void *args);
void *getMin(void *args);

int main(int argc, char *argv[])
{
    size = argc - 1;
    int i;
    pthread_t *thread_ids;
    thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * 3);

    // get total number of inputs
    printf("You entered: %d numbers\n", size);

    ptr = (int *)malloc(argc * sizeof(int));
    // catching input error
    if (ptr == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    // Assign values
    for (i = 0; i < size; ++i)
    {
        ptr[i] = atoi(argv[i + 1]);
    }
    // threading
    printf("=============\n");
    pthread_create(&thread_ids[0], NULL, getAverage, (void *)ptr);
    pthread_create(&thread_ids[1], NULL, getMax, (void *)ptr);
    pthread_create(&thread_ids[2], NULL, getMin, (void *)ptr);
    // join threading
    for (i = 0; i < 3; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }

    printf("The average value is: %lf\n", average);
    printf("The minimum value is: %d\n", minimum);
    printf("The maximum value is: %d\n", maximum);

    return 0;
}

void *getAverage(void *args)
{

    int *array = (int *)args;
    int sum = 0;
    int i;

    for (i = 0; i < size; i++)
    {
        sum += array[i];
    }

    maximum = array[1];
    average = (double)(sum) / (double)(size);
    pthread_exit(NULL);
}

void *getMax(void *args)
{
    int *array = (int *)args;
    int max = array[0];
    int i;

    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    maximum = max;

    pthread_exit(NULL);
}

void *getMin(void *args)
{
    int *array = (int *)args;
    int min = array[0];
    int i;

    for (i = 1; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }

    minimum = min;

    pthread_exit(NULL);
}