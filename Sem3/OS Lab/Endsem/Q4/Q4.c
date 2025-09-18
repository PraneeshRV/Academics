#include <stdio.h>

int main() {
    int frames, pages, page_faults = 0;
    int ref_string[100], frame[100], flag, front = 0;

    printf("Enter  no. of frames: ");
    scanf("%d", &frames);

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("Enter no. pages: ");
    scanf("%d", &pages);

    
    printf("Enter reference string: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &ref_string[i]);
    }

    
    for (int i = 0; i < pages; i++) {
        flag = 0;

        
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref_string[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            frame[front] = ref_string[i];
            front = (front + 1) % frames;
            page_faults++;
        }
	
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
