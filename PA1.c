#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t mutex;
sem_t first_;
int ctr = 0;

int i = -1;

void* increment_t1(void *arg)
{
    if(!ctr)
    {
        i = 0;
        ctr = 1;
        sem_post(&first_);
    }
    

    for(int j=0; j<100; j++)
    {
        sem_wait(&mutex);
        printf("T1");
            i++;
        printf("%d\n", i);    
        sem_post(&mutex);
    }   

}

void* increment_t2(void *arg)
{
    sem_wait(&first_);

    for(int j=0; j<100; j++)
    {
        sem_wait(&mutex);
        printf("T2");
            i++;
        printf("%d\n", i);
        sem_post(&mutex);
    }  
    
    sem_post(&first_);
}

int main()
{
    sem_init(&mutex, 1, 1);
    sem_init(&first_, 1, 0);

    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, *increment_t1, NULL);
    pthread_create(&t2, NULL, *increment_t2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Value of Counter : %d", i);

    sem_destroy(&mutex);
    return 0;
}