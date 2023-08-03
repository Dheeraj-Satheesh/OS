#include <stdio.h>
#include <limits.h>
#define MAX_FRAMES 4
int isPagePresent(int frames[], int num_frames, int page)
{
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}
int findOptimal(int pages[], int n, int frames[], int num_frames, int current_index)
{
    int farthest_index = -1;
    int farthest_page = -1;
    for (int i = 0; i < num_frames; i++)
    {
        int page = frames[i];
        int j;
        for (j = current_index; j < n; j++)
        {
            if (pages[j] == page)
            {
                if (j > farthest_index)
                {
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
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] == farthest_page)
            return i;
    }
    return 0;
}
int optimal(int pages[], int n, int num_frames)
{
    int frames[MAX_FRAMES];
    int page_faults = 0;
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int current_page = pages[i];
        if (!isPagePresent(frames, num_frames, current_page))
        {
            int index = findOptimal(pages, n, frames, num_frames, i + 1);
            frames[index] = current_page;
            page_faults++;
            printf("Page fault: %d -> [", current_page);
            for (int j = 0; j < num_frames - 1; j++)
                printf("%d, ", frames[j]);
            printf("%d]\n", frames[num_frames - 1]);
        }
    }
    return page_faults;
}
int main()
{
    int pages[] = {0,4,3,2,1,4,6,3,0,8,9,3,8,5};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames;
    printf("Enter the number of frames (2, 3, or 4): ");
    scanf("%d", &num_frames);
    int page_faults = optimal(pages, num_pages, num_frames);
    printf("\nTotal page faults: %d\n", page_faults);
    return 0;
}

