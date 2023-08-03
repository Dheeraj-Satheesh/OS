#include <stdio.h>

#define MAX_PROCESSES 100

int main()
{
    int n; // Number of processes
    int arrival_time[MAX_PROCESSES];
    int burst_time[MAX_PROCESSES];
    int completion_time[MAX_PROCESSES];
    int turnaround_time[MAX_PROCESSES];
    int waiting_time[MAX_PROCESSES];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);

        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Calculate completion time, turnaround time, and waiting time for each process
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < arrival_time[i])
        {
            current_time = arrival_time[i];
        }

        completion_time[i] = current_time + burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];

        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];

        current_time = completion_time[i];
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    // Calculate and display average waiting time and average turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
