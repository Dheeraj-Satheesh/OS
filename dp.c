#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define LEFT_PHILOSOPHER (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT_PHILOSOPHER (philosopher_id + 1) % NUM_PHILOSOPHERS

typedef enum { THINKING, HUNGRY, EATING } PhilosopherState;

typedef struct {
    PhilosopherState states[NUM_PHILOSOPHERS];
    pthread_mutex_t mutex;
    pthread_cond_t conditions[NUM_PHILOSOPHERS];
} DiningPhilosophersMonitor;

DiningPhilosophersMonitor monitor;

void initialize_monitor(DiningPhilosophersMonitor* monitor) {
    int i;
    pthread_mutex_init(&monitor->mutex, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        monitor->states[i] = THINKING;
        pthread_cond_init(&monitor->conditions[i], NULL);
    }
}

void pickup_chopsticks(DiningPhilosophersMonitor* monitor, int philosopher_id) {
    pthread_mutex_lock(&monitor->mutex);
    monitor->states[philosopher_id] = HUNGRY;
    test(philosopher_id); // Check if the philosopher can start eating
    while (monitor->states[philosopher_id] != EATING) {
        pthread_cond_wait(&monitor->conditions[philosopher_id], &monitor->mutex);
    }
    pthread_mutex_unlock(&monitor->mutex);
}

void return_chopsticks(DiningPhilosophersMonitor* monitor, int philosopher_id) {
    pthread_mutex_lock(&monitor->mutex);
    monitor->states[philosopher_id] = THINKING;
    test(LEFT_PHILOSOPHER); // Check if the left philosopher can start eating
    test(RIGHT_PHILOSOPHER); // Check if the right philosopher can start eating
    pthread_mutex_unlock(&monitor->mutex);
}

void test(int philosopher_id) {
    if (monitor.states[philosopher_id] == HUNGRY &&
        monitor.states[LEFT_PHILOSOPHER] != EATING &&
        monitor.states[RIGHT_PHILOSOPHER] != EATING) {
        monitor.states[philosopher_id] = EATING;
        pthread_cond_signal(&monitor.conditions[philosopher_id]);
    }
}

void* philosopher_thread(void* arg) {
    int philosopher_id = (int)arg;
    int i;

    for (i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(rand() % 3 + 1); // Simulate thinking

        printf("Philosopher %d is hungry and trying to pick up chopsticks.\n", philosopher_id);
        pickup_chopsticks(&monitor, philosopher_id);

        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(rand() % 3 + 1); // Simulate eating

        printf("Philosopher %d finished eating and returned chopsticks.\n", philosopher_id);
        return_chopsticks(&monitor, philosopher_id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    int i;

    srand(time(NULL));

    initialize_monitor(&monitor);

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher_thread, &philosopher_ids[i]);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
