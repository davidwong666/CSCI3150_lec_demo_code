#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int shared = 50;

void *add(void *input)
{

    int mylocal1 = shared;
    printf("add thread:\tshared\t= %d\n", shared);

    mylocal1 += 10;
    printf("add thread:\tmylocal1\t= %d\n", mylocal1);

    srand(time(NULL));
    sleep(rand() % 3);

    shared = mylocal1;
    printf("add thread write back:\tshared\t= %d\n", shared);

    pthread_exit(NULL);
}

void *minus(void *input)
{

    int mylocal2 = shared;
    printf("minus thread:\tshared\t= %d\n", shared);

    mylocal2 -= 100;
    printf("minus thread:\tmylocal2\t= %d\n", mylocal2);

    srand(time(NULL));
    sleep(rand() % 4);
    printf("minus thread write back:\tshared\t= %d\n", shared);

    shared = mylocal2;

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid1, tid2;
    int input = 0;
    pthread_create(&tid1, NULL, add, NULL);
    pthread_create(&tid2, NULL, minus, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("main thread:\tshared\t= %d\n", shared);
    return 0;
}
