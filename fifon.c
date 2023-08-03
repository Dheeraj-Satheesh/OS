#include <stdio.h>
#include <stdbool.h>
#define MAX_FRAMES 4
void fifo(int pages[], int n, int num_frames)
{
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int page_hits = 0;
    int frame_index = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int current_page = pages[i];

        if (isPagePresent(frames, num_frames, current_page))
        {
            page_hits++;

            printf("Page hit: %d -> [", current_page);
            for (int j = 0; j < num_frames - 1; j++)
                printf("%d, ", frames[j]);
            printf("%d]\n", frames[num_frames - 1]);
        }
        else
        {
            frames[frame_index] = current_page;
            frame_index = (frame_index + 1) % num_frames;
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
int main()
{
    int pages[] = {7, 0, 1,2, 0, 3, 0, 4, 2, 3, 0, 3,1,2,0};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames;
    printf("Enter the number of frames (2, 3, or 4): ");
    scanf("%d", &num_frames);
    fifo(pages, num_pages, num_frames);
    return 0;
}
