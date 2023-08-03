#include <stdio.h>
#include <stdbool.h>

// Maximum number of processes and resources
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


// Function to check if the system is in a safe state
bool isSafe(int available[], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processes, int resources)
{
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int i, j, count = 0;

    // Initialize work array with available resources
    for (i = 0; i < resources; i++)
        work[i] = available[i];


    // Find an unfinished process whose needs can be satisfied
    while (count < processes)
    {
        bool found = false;
        for (i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (j = 0; j < resources; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    safeSequence[count] = i;
                    count++;
                    found = true;
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
        return true; // System is in a safe state
    }
    else
    {
        printf("System is in an unsafe state.\n");
        return false; // System is in an unsafe state
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
    // Check if the system is in a safe state
    isSafe(available, max, allocation, need, processes, resources);
    return 0;
}
