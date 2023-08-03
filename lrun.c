#include <stdio.h>
#include <stdbool.h>
#define MAX_FRAMES 4

bool isPagePresent(int frames[], int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

int findLRU(int indexes[], int num_frames) {
    int min_index = 0;
    int min_value = indexes[0];
    for (int i = 1; i < num_frames; i++) {
        if (indexes[i] < min_value) {
            min_value = indexes[i];
            min_index = i;
        }
    }
    return min_index;
}

void lru(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int indexes[MAX_FRAMES];
    int page_faults = 0;
    int page_hits = 0;
    int next_frame = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        indexes[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        if (isPagePresent(frames, num_frames, current_page)) {
            page_hits++;
            indexes[next_frame] = i + 1;
            printf("Page hit: %d -> [", current_page);
            for (int j = 0; j < num_frames - 1; j++)
                printf("%d, ", frames[j]);
            printf("%d]\n", frames[num_frames - 1]);
        } else {
            int lru_index = findLRU(indexes, num_frames);
            frames[lru_index] = current_page;
            indexes[lru_index] = i + 1;
            page_faults++;
            printf("Page fault: %d -> [", current_page);
            for (int j = 0; j < num_frames - 1; j++)
                printf("%d, ", frames[j]);
            printf("%d]\n", frames[num_frames - 1]);
        }
    }

    printf("\nTotal page hits: %d\n", page_hits);
    printf("Total page faults: %d\n", page_faults);
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

    lru(pages, num_pages, num_frames);
    return 0;
}
