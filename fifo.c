#include <stdio.h>
#define MAX_FRAMES 4
int fifo(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int next_frame = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;
    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int is_page_fault = 1;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == current_page) {
                is_page_fault = 0;
                break;
            }
        }
        if (is_page_fault) {
            frames[next_frame] = current_page;
            next_frame = (next_frame + 1) % num_frames;
            page_faults++;
            printf("Page fault: %d -> [", current_page);
            for (int k = 0; k < num_frames - 1; k++)
                printf("%d, ", frames[k]);
            printf("%d]\n", frames[num_frames - 1]);
        }
    }
    return page_faults;
}
int main() {
    int num_pages;
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages];
    printf("Enter the page references:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }
    int num_frames;
    printf("Enter the number of frames (2, 3, or 4): ");
    scanf("%d", &num_frames);
    int page_faults = fifo(pages, num_pages, num_frames);
    printf("\nTotal page faults: %d\n", page_faults);
    return 0;
}
