#include <stdio.h>
#include <pthread.h>

// Shared variable
int shared_variable = 0;

// Busy wait solution
void busy_wait()
{
    while (shared_variable != 1);
}

// Function to read the shared variable
void* read_shared_variable(void* arg)
{
    printf("Reading shared variable: %d\n", shared_variable);
    return NULL;
}

// Function to write the shared variable
void* write_shared_variable(void* arg)
{
    printf("Writing shared variable\n");
    shared_variable = 1;
    return NULL;
}

int main()
{
    pthread_t read_thread, write_thread;

    // Create threads
    pthread_create(&read_thread, NULL, read_shared_variable, NULL);
    pthread_create(&write_thread, NULL, write_shared_variable, NULL);

    // Wait for the threads to finish
    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    // Use busy wait to ensure the shared variable is updated
    busy_wait();

    // Print the final value of the shared variable
    printf("Final shared variable: %d\n", shared_variable);

    return 0;
}
