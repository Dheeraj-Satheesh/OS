#include <stdio.h>
#define MAX_FRAMES 4
int findLRU(int frames[], int n, int indexes[], int num_frames) {
    int i, min_index = 0, min_value = indexes[0];

    for (i = 1; i < num_frames; i++) {
        if (indexes[i] < min_value) {
            min_value = indexes[i];
            min_index = i;
        }
    }
    return min_index;
}
int lru(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int indexes[MAX_FRAMES];
    int page_faults = 0;
    int page_hits = 0;
    int next_frame = 0;
    int i, j, k;

    for (i = 0; i < num_frames; i++) {
        frames[i] = -1;
        indexes[i] = 0;
    }
    for (i = 0; i < n; i++) {
        int current_page = pages[i];
        int is_page_fault = 1;
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == current_page) {
                is_page_fault = 0;
                indexes[j] = i + 1;
                page_hits++;
                printf("Page hit: %d -> [", current_page);
                for (k = 0; k < num_frames - 1; k++)
                    printf("%d, ", frames[k]);
                printf("%d]\n", frames[num_frames - 1]);
                break;
            }
        }
        if (is_page_fault) {
            int lru_index = findLRU(frames, n, indexes, num_frames);
            frames[lru_index] = current_page;
            indexes[lru_index] = i + 1;
            page_faults++;
            printf("Page fault: %d -> [", current_page);
            for (k = 0; k < num_frames - 1; k++)
                printf("%d, ", frames[k]);
            printf("%d]\n", frames[num_frames - 1]);
        }
    }
    printf("\nTotal page hits: %d\n", page_hits);
    printf("Total page faults: %d\n", page_faults);

    return page_faults;
}
int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames;
    printf("Enter the number of frames (2, 3, or 4): ");
    scanf("%d", &num_frames);
    int page_faults = lru(pages, num_pages, num_frames);
    return 0;
}
