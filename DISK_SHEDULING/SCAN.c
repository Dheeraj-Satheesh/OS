#include <stdio.h>
#include <stdlib.h>

void SCAN(int requests[], int num_requests, int head_position, int total_tracks, int direction) {
    int total_seek_time = 0;

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

    // Visit requests based on the chosen direction
    if (direction == 1) {
        // Moving towards larger cylinder numbers (right)
        for (int j = i; j < num_requests; j++) {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }

        // Add the seek time to the last track
        total_seek_time += abs(total_tracks - 1 - head_position);

        // Move the head to the last track
        head_position = total_tracks - 1;
        printf(" -> %d", head_position);

        // Visit requests in the reverse direction
        for (int j = i - 1; j >= 0; j--) {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
    } else if (direction == 0) {
        // Moving towards smaller cylinder numbers (left)
        for (int j = i - 1; j >= 0; j--) {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }

        // Add the seek time to the first track
        total_seek_time += abs(head_position);

        // Move the head to the first track
        head_position = 0;
        printf(" -> %d", head_position);

        // Visit requests in the forward direction
        for (int j = i; j < num_requests; j++) {
            printf(" -> %d", requests[j]);
            total_seek_time += abs(requests[j] - head_position);
            head_position = requests[j];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests;
    int head_position;
    int total_tracks;
    int direction;

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int requests[num_requests];

    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head_position);

    printf("Enter the total number of tracks: ");
    scanf("%d", &total_tracks);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    SCAN(requests, num_requests, head_position, total_tracks, direction);

    return 0;
}
