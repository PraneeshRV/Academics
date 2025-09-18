#include <stdio.h>

int main() {
    int frames, pages, page_faults = 0;
    int ref_string[50], frame[10], flag, front = 0;

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    // Input the reference string
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &ref_string[i]);
    }

    // FIFO Page Replacement Algorithm
    for (int i = 0; i < pages; i++) {
        flag = 0;

        // Check if the page is already present in any frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref_string[i]) {
                flag = 1;  // Page hit
                break;
            }
        }

        // If the page is not present in any frame, replace the oldest one
        if (flag == 0) {
            frame[front] = ref_string[i];
            front = (front + 1) % frames;  // Move the front to the next frame
            page_faults++;
        }

        // Display the current state of frames
        printf("\nFrames after accessing page %d: ", ref_string[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
