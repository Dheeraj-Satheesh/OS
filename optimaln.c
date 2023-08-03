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

int findOptimal(int pages[], int n, int frames[], int num_frames, int current_index) {
    int farthest_index = -1;
    int farthest_page = -1;
    for (int i = 0; i < num_frames; i++) {
        int page = frames[i];
        int j;
        for (j = current_index; j < n; j++) {
            if (pages[j] == page) {
                if (j > farthest_index) {
                    farthest_index = j;
                    farthest_page = page;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    if (farthest_page == -1)
        return 0;
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == farthest_page)
            return i;
    }
    return 0;
}

void optimal(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int page_hits = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        if (isPagePresent(frames, num_frames, current_page)) {
            page_hits++;
            printf("Page hit: %d -> [", current_page);
            for (int j = 0; j < num_frames - 1; j++)
                printf("%d, ", frames[j]);
            printf("%d]\n", frames[num_frames - 1]);
        } else {
            int index = findOptimal(pages, n, frames, num_frames, i + 1);
            frames[index] = current_page;
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

    optimal(pages, num_pages, num_frames);
    return 0;
}
