#include <stdio.h>

typedef struct {
    int value;
} counting_semaphore;

void sem_init(counting_semaphore *sem, int init_value) {
    sem->value = init_value;
}

void sem_wait(counting_semaphore *sem) {
    while (sem->value <= 0) {
        // Wait until the semaphore value becomes positive
    }
    sem->value--;
}

void sem_signal(counting_semaphore *sem) {
    sem->value++;
}

int main() {
    counting_semaphore semaphore1;
    counting_semaphore semaphore2;
    sem_init(&semaphore1, 1);
    sem_init(&semaphore2, 1);

    int deadlock_detected = 0; // Flag to track if a deadlock is detected

    // Process 1
    sem_wait(&semaphore1);
    printf("Process 1: Acquired semaphore1\n");

    // Process 2
    if (semaphore2.value <= 0) {
        printf("Potential deadlock detected: Process 2 is waiting for semaphore2\n");
        deadlock_detected = 1;
    }
    sem_wait(&semaphore2);
    printf("Process 2: Acquired semaphore2\n");

    // Process 1 is waiting for semaphore2 to be released
    sem_signal(&semaphore1);

    // Process 2 is waiting for semaphore1 to be released
    sem_signal(&semaphore2);

    if (deadlock_detected) {
        printf("Deadlock detected!\n");
    }
    return 0;
}
