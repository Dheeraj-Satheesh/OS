#include <stdio.h>
#include <stdlib.h>
int main()
{
    int queue[1000], head, n, total_seek = 0;
    printf("Enter the size of the disk queue: ");
    scanf("%d", &n);
    printf("Enter the disk queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    // Calculate total seek time
    for (int i = 0; i < n; i++) {
        total_seek += abs(head - queue[i]);
        head = queue[i];
    }
    printf("Total Seek Time: %d\n", total_seek);
    return 0;
}
