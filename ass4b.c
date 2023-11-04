/*
Assignment No 4b
B. Thread synchronization and mutual exclusion using mutex. 
Application to demonstrate: Reader-
Writer problem with reader priority.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_ITERATIONS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
int shared_data;

void *writer(void *arg)
{
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        int random_number = rand() % 100; // Generate a random number

        pthread_mutex_lock(&mutex);
        shared_data = random_number;
        printf("Writer wrote: %d\n", shared_data);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate some writing time
    }
    pthread_exit(NULL);
}

void *reader(void *arg)
{
    int reader_id = *((int *)arg);
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        pthread_barrier_wait(&barrier);

        pthread_mutex_lock(&mutex);
        int data = shared_data;
        printf("Reader %d: Item READ from buffer: %d\n", reader_id, data);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate some reading time
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));
    pthread_t writer_thread, reader_threads[NUM_READERS];
    int reader_ids[NUM_READERS] = {1, 2, 3};

    pthread_barrier_init(&barrier, NULL, NUM_READERS);

    pthread_create(&writer_thread, NULL, writer, NULL);
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    pthread_join(writer_thread, NULL);
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(reader_threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
