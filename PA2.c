#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Lock free programming using Peterson's Solution*/

int flag[2];
int turn = 0;

int counter = 0;

void* increment(void* arg)
{
    for(int i=0; i<10000000; i++)
    {
        flag[0] = 1;
        turn = 1;

        while (flag[1] && turn==1);
        
        counter++;

        flag[0] = 0;
    }
}

void* decrement(void* arg)
{
    for(int j=0; j<10000000; j++)
    {
        flag[1] = 1;
        turn = 0;

        while (flag[0] && turn==0);
        
        counter--;

        flag[1] = 0;
    }
}

int main(int argc, char const *argv[])
{
    pthread_t p1, p2;
    pthread_create(&p1, NULL, *increment, NULL);
    pthread_create(&p2, NULL, *decrement, NULL);
    printf("%d", counter);
    return 0;
}
