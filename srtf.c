#include <stdio.h>

// Function to perform SJF preemptive scheduling
void sjfPreemptive(int processes[], int n, int burstTime[], int arrivalTime[]) {
    int remainingBurstTime[n];
    int completionTime[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int currentTime = 0;
    int completedProcesses = 0;

    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = burstTime[i];
    }

    while (completedProcesses < n) {
        int shortestProcess = -1;
        int shortestBurstTime = 9999999;

        // Find the process with the shortest burst time that has arrived and not yet completed
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingBurstTime[i] > 0 && remainingBurstTime[i] < shortestBurstTime) {
                shortestProcess = i;
                shortestBurstTime = remainingBurstTime[i];
            }
        }

        // If no process is found (shouldn't happen), increment the current time and continue
        if (shortestProcess == -1) {
            currentTime++;
            continue;
        }

        // Execute the shortest process for one time unit
        remainingBurstTime[shortestProcess]--;

        // If the process is completed, calculate its completion time and update completedProcesses count
        if (remainingBurstTime[shortestProcess] == 0) {
            completionTime[shortestProcess] = currentTime + 1;
            completedProcesses++;
        }

        currentTime++;
    }

    // Calculate waiting time and turnaround time for each process
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Print the details of each process
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i], arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    // Calculate and print the average waiting time and average turnaround time
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burstTime[n];
    int arrivalTime[n];

    printf("Enter the arrival times and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
        processes[i] = i + 1;
    }

    sjfPreemptive(processes, n, burstTime, arrivalTime);

    return 0;
}
