#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 4
#define NUM_ITEMS 8

int buffer[BUFFER_SIZE];
int buffer_index = 0;

pthread_mutex_t mutex;
pthread_cond_t full_cond, empty_cond;

void* producer(void* arg) {
    int item = 1;

    while (item <= NUM_ITEMS) {
        pthread_mutex_lock(&mutex);

        // Wait until buffer is not full
        while (buffer_index == BUFFER_SIZE) {
            pthread_cond_wait(&empty_cond, &mutex);
        }

        // Produce item and add it to the buffer
        buffer[buffer_index] = item++;
        buffer_index++;

        printf("Produced item: %d\n", buffer[buffer_index - 1]);

        // Signal that buffer is not empty
        pthread_cond_signal(&full_cond);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait until buffer is not empty
        while (buffer_index == 0) {
            pthread_cond_wait(&full_cond, &mutex);
        }

        // Consume item from the buffer
        int item = buffer[--buffer_index];
        printf("Consumed item: %d\n", item);

        // Signal that buffer is not full
        pthread_cond_signal(&empty_cond);

        pthread_mutex_unlock(&mutex);

        if (item == NUM_ITEMS) {
            break;
        }
    }

    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full_cond, NULL);
    pthread_cond_init(&empty_cond, NULL);

    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full_cond);
    pthread_cond_destroy(&empty_cond);

    return 0;
}
