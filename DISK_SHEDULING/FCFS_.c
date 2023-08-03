#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void FCFS(int requests[], int num_requests, int head_position)
{
    int total_seek_time = 0;
    int current_position = head_position;
    printf("Sequence: %d", current_position);
    for (int i = 0; i < num_requests; i++)
    {
        int distance = abs(requests[i] - current_position);
        total_seek_time += distance;
        current_position = requests[i];
        printf(" -> %d", current_position);
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main()
{
    int num_requests;
    int head_position;
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);
    int requests[num_requests];
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < num_requests; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head_position);
    FCFS(requests, num_requests, head_position);
    return 0;
}

