#include <stdio.h>
// Maximum number of processes and resources
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
// Function to check if the requested resources can be granted
int isSafe(int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processes, int resources)
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int i, j;
    // Initialize work array with available resources
    for (i = 0; i < resources; i++)
        work[i] = available[i];
    // Find an unfinished process whose needs can be satisfied
    int count = 0;
    while (count < processes)
    {
        int found = 0;
        for (i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                int canAllocate = 1;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (j = 0; j < resources; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        // If no process found, break the loop
        if (!found)
            break;
    }
    // Check if all processes finished
    if (count == processes)
    {
        printf("System is in a safe state.\nSafe Sequence: ");
        for (i = 0; i < processes; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
// System is in a safe state
    }
    else
    {
        printf("System is in an unsafe state.\n");
         // System is in an unsafe state
    }
}
// Function to request resources
void requestResources(int request[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int process, int resources)
{
    int i;
    for (i = 0; i < resources; i++)
    {
        if (request[i] > need[process][i] || request[i] > available[i])
        {
            printf("Request exceeds maximum need or available resources!\n");
            return;
        }
    }
    for (i = 0; i < resources; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    if (isSafe(available, max, allocation, need, process, resources))
        printf("Request granted. System is in a safe state.\n");
    else
    {
        // Rollback the allocation if the system becomes unsafe
        printf("Request denied. System will enter an unsafe state. Rolling back the allocation.\n");
        for (i = 0; i < resources; i++)
        {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}
int main()
{
    int processes, resources;
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);
    printf("Enter the available resources:\n");
    for (i = 0; i < resources; i++)
        scanf("%d", &available[i]);
    printf("Enter the maximum resource allocation for each process:\n");
    for (i = 0; i < processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < resources; j++)
            scanf("%d", &max[i][j]);
    }
    printf("Enter the current resource allocation for each process:\n");
    for (i = 0; i < processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < resources; j++)
            scanf("%d", &allocation[i][j]);
    }
    // Calculate the need matrix
    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    // Simulating resource requests
    int request[MAX_RESOURCES];
    int process;
    printf("Enter the process number making the resource request: ");
    scanf("%d", &process);
    printf("Enter the resource request for process %d:\n", process);
    for (i = 0; i < resources; i++)
        scanf("%d", &request[i]);
    requestResources(request, available, max, allocation, need, process, resources);
    return 0;
}
