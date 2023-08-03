#include <stdio.h>
#include <stdlib.h>
void CLOOK(int requests[], int num_requests, int head_position) {
    int total_seek_time = 0;
    int direction = 1; // 1 indicates moving towards larger cylinder numbers
    printf("Sequence: %d", head_position);
    // Sort the requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    // Find the index where the head position should be inserted to maintain sorted order
    int i;
    for (i = 0; i < num_requests; i++) {
        if (requests[i] > head_position) {
            break;
        }
    }
    // Visit requests in the forward direction
    for (int j = i; j < num_requests; j++) {
        printf(" -> %d", requests[j]);
        total_seek_time += abs(requests[j] - head_position);
        head_position = requests[j];
    }

    // Move the head to the first track
    printf(" -> %d", requests[0]);
    total_seek_time += abs(requests[0] - head_position);
    head_position = requests[0];

    // Visit requests in the forward direction again
    for (int j = 1; j < i; j++) {
        printf(" -> %d", requests[j]);
        total_seek_time += abs(requests[j] - head_position);
        head_position = requests[j];
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main()
{
    int num_requests;
    int head_position;
    int total_tracks;

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
    CLOOK(requests, num_requests, head_position);
    return 0;
}

