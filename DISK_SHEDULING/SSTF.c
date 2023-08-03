#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
int findClosestRequest(int requests[], bool visited[], int head_position, int num_requests)
{
    int min_distance = INT_MAX;
    int closest_request = -1;
    for (int i = 0; i < num_requests; i++)
    {
        int distance = abs(requests[i] - head_position);
        if (!visited[i] && distance < min_distance)
        {
            min_distance = distance;
            closest_request = i;
        }
    }
    return closest_request;
}
void SSTF(int requests[], int num_requests, int head_position)
{
    int total_seek_time = 0;
    bool visited[num_requests];
    for (int i = 0; i < num_requests; i++)
    {
        visited[i] = false;
    }
    printf("Sequence: %d", head_position);
    for (int i = 0; i < num_requests; i++)
    {
        int closest_request = findClosestRequest(requests, visited, head_position, num_requests);
        visited[closest_request] = true;
        total_seek_time += abs(requests[closest_request] - head_position);
        head_position = requests[closest_request];
        printf(" -> %d", head_position);
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
    SSTF(requests, num_requests, head_position);
    return 0;
}

