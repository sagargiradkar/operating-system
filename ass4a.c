/*
Assignment No.4 A
A. Thread synchronization using counting semaphores. Application to demonstrate: producer-
consumer problem with counting semaphores and mutex.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct
{
        int buff[20];
        sem_t full, empty;

} shared;

shared sh;
int item;
int in = 0, out = 0;
pthread_mutex_t mutex;

void *producer()
{
        int ptid;
        int k = 0;
        while (k < 5)
        {
                item = rand() % 100;
                sem_wait(&sh.empty);
                pthread_mutex_lock(&mutex);

                sh.buff[in++] = item;
                printf("\nproducer item:%d\n", item);
                pthread_mutex_unlock(&mutex);
                sem_post(&sh.full);
                sleep(2);
                k++;
        }
        exit(0);
}

void *consumer()
{
        int ctid;
        while (1)
        {
                while (out <= in)
                {
                        sem_wait(&sh.full);
                        pthread_mutex_lock(&mutex);
                        item = sh.buff[out++];
                        printf("\nconsumer item:%d\n", item);

                        pthread_mutex_unlock(&mutex);
                        sem_post(&sh.empty);
                        sleep(2);
                }
        }
}

int main()
{
        pthread_t ptid1, ctid1;
        sem_init(&sh.empty, 0, 20);
        sem_init(&sh.full, 0, 0);
        pthread_mutex_init(&mutex, NULL);

        pthread_create(&ptid1, NULL, producer, NULL);
        // pthread_create(&ptid2,NULL,producer,NULL);
        pthread_create(&ctid1, NULL, consumer, NULL);

        pthread_join(ptid1, NULL);
        pthread_join(ctid1, NULL);

        return 0;
}
