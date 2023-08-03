#include <stdio.h>
#include <stdlib.h>
void LOOK(int requests[], int num_requests, int head_position, int direction)
{
    int total_seek_time = 0;
    printf("Sequence: %d", head_position);
    // Find the maximum and minimum track numbers in the request list
    int max_track = requests[0];
    int min_track = requests[0];
    for (int i = 1; i < num_requests; i++)
    {
        if (requests[i] > max_track)
        {
            max_track = requests[i];
        }
        if (requests[i] < min_track)
        {
            min_track = requests[i];
        }
    }
    // Sort the requests in ascending order
    for (int i = 0; i < num_requests - 1; i++)
    {
        for (int j = 0; j < num_requests - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    // Find the index where the head position should be inserted to maintain sorted order
    int i;
    for (i = 0; i < num_requests; i++)
    {
        if (requests[i] > head_position)
        {
            break;
        }
    }
    if (direction == 0)
    {
        // Visit requests in the reverse direction
        for (int j = i - 1; j >= 0; j--)
        {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
        // Visit requests in the forward direction
        for (int j = i; j < num_requests; j++)
        {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
    }
    else
    {
        // Visit requests in the forward direction
        for (int j = i; j < num_requests; j++)
        {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
        // Visit requests in the reverse direction
        for (int j = i - 1; j >= 0; j--)
        {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main()
{
    int num_requests;
    int head_position;
    int direction_choice;
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
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction_choice);
    LOOK(requests, num_requests, head_position, direction_choice);
    return 0;
}
