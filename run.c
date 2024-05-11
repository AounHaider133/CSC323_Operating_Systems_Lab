#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *runner(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    pthread_attr_t attr1, attr2;
    int *sum1, *sum2;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return -1;
    }

    /* set the attributes of the threads */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    /* create the first thread */
    pthread_create(&tid1, &attr1, runner, argv[1]);
    pthread_join(tid1, (void **)&sum1);
    printf("Thread 1 sum = %d\n", *sum1);

    /* create the second thread */
    pthread_create(&tid2, &attr2, runner, argv[2]);
    pthread_join(tid2, (void **)&sum2);
    printf("Thread 2 sum = %d\n", *sum2);

    return 0;
}

void *runner(void *param)
{
    int i, upper = atoi((char *)param);
    int *sum = (int *)malloc(sizeof(int));
    *sum = 0;

    for (i = 0; i < upper; i++)
        *sum += i;

    pthread_exit((void *)sum);
}

