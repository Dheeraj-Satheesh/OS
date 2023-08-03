#include <stdio.h>
// Function to perform SJF non-preemptive scheduling
void sjfNonPreemptive(int processes[], int n, int burstTime[], int arrivalTime[]) {
    int completionTime[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Initialize an array to keep track of processes that are not yet completed
    int remainingProcesses[n];
    for (int i = 0; i < n; i++) {
        remainingProcesses[i] = burstTime[i];
    }

    int currentTime = 0;
    int completedProcesses = 0;

    // Perform the scheduling until all processes are completed
    while (completedProcesses < n) {
        int shortestProcess = -1;
        int shortestBurstTime = 9999999;

        // Find the process with the shortest burst time that has arrived and not yet completed
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingProcesses[i] > 0 && remainingProcesses[i] < shortestBurstTime) {
                shortestProcess = i;
                shortestBurstTime = remainingProcesses[i];
            }
        }

        // If no process is found (should not happen), increment the current time and continue
        if (shortestProcess == -1) {
            currentTime++;
            continue;
        }

        // Mark the process as completed and calculate its completion time
        completionTime[shortestProcess] = currentTime + remainingProcesses[shortestProcess];
        currentTime = completionTime[shortestProcess];
        remainingProcesses[shortestProcess] = 0;
        completedProcesses++;

        // Calculate waiting time and turnaround time for the completed process
        waitingTime[shortestProcess] = currentTime - burstTime[shortestProcess] - arrivalTime[shortestProcess];
        turnaroundTime[shortestProcess] = completionTime[shortestProcess] - arrivalTime[shortestProcess];

        // Update the total waiting and turnaround times
        totalWaitingTime += waitingTime[shortestProcess];
        totalTurnaroundTime += turnaroundTime[shortestProcess];
    }

    // Calculate and print the average waiting time and average turnaround time
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nProcess\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i], arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

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

    sjfNonPreemptive(processes, n, burstTime, arrivalTime);

    return 0;
}
