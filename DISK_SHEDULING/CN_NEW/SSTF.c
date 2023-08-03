#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int findShortestSeek(int queue[], int head, int n, int visited[]) {
    int shortest_seek = INT_MAX;
    int shortest_index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int seek = abs(head - queue[i]);
            if (seek < shortest_seek) {
                shortest_seek = seek;
                shortest_index = i;
            }
        }
    }
    return shortest_index;
}
int main() {
    int queue[1000], head, n, total_seek = 0, visited[1000] = {0};

    printf("Enter the size of the disk queue: ");
    scanf("%d", &n);

    printf("Enter the disk queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    // Process requests
    for (int i = 0; i < n; i++) {
        int shortest_index = findShortestSeek(queue, head, n, visited);
        visited[shortest_index] = 1;
        total_seek += abs(head - queue[shortest_index]);
        head = queue[shortest_index];
    }
    printf("Total Seek Time: %d\n", total_seek);
    return 0;
}
