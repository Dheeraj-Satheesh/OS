#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void CSCAN(int requests[], int num_requests, int head_position, int total_tracks, bool direction_right)
{
    int total_seek_time = 0;
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
    int start_index = 0;
    // Find the index where the head position should be inserted to maintain sorted order
    for (int i = 0; i < num_requests; i++)
    {
        if (requests[i] >= head_position)
        {
            start_index = i;
            break;
        }
    }
    printf("Sequence: %d", head_position);
    if (direction_right)
    {
        // Visit requests in the forward direction
        for (int i = start_index; i < num_requests; i++)
        {
            printf(" -> %d", requests[i]);
            total_seek_time += abs(requests[i] - head_position);
            head_position = requests[i];
        }
        // Move the head to the end of the disk
        printf(" -> %d", total_tracks - 1);
        total_seek_time += abs(total_tracks - 1 - head_position);
        head_position = total_tracks - 1;
        // Return to track 0
        printf(" -> 0");
        total_seek_time += abs(head_position - 0);
        head_position = 0;
        // Visit requests from track 0 until the start_index
        for (int i = 0; i < start_index; i++)
        {
            printf(" -> %d", requests[i]);
            total_seek_time += abs(requests[i] - head_position);
            head_position = requests[i];
        }
    }
    else
    {
        // Visit requests in the reverse direction
        for (int i = start_index - 1; i >= 0; i--)
        {
            printf(" -> %d", requests[i]);
            total_seek_time += abs(requests[i] - head_position);
            head_position = requests[i];
        }
        // Move the head to the beginning of the disk
        printf(" -> 0");
        total_seek_time += abs(head_position - 0);
        head_position = 0;
        // Visit requests from track 0 until the end of the disk
        for (int i = num_requests - 1; i >= start_index; i--)
        {
            printf(" -> %d", requests[i]);
            total_seek_time += abs(requests[i] - head_position);
            head_position = requests[i];
        }
        // Move the head to the end of the disk
        printf(" -> %d", total_tracks - 1);
        total_seek_time += abs(total_tracks - 1 - head_position);
        head_position = total_tracks - 1;
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main()
{
    int num_requests;
    int head_position;
    int total_tracks;
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
    printf("Enter the total number of tracks: ");
    scanf("%d", &total_tracks);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction_choice);
    bool direction_right = (direction_choice == 1);
    CSCAN(requests, num_requests, head_position, total_tracks, direction_right);
    return 0;
}
