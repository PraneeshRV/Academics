#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    
    for(i = 1; i < n; ++i) {
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    
    return pos;
}

void LRU(int pages[], int n, int framesCount) {
    int frames[framesCount], time[framesCount];
    int counter = 0, pageFaults = 0, i, j, pos, flag1, flag2;

    // Initialize frames and time array
    for(i = 0; i < framesCount; ++i) {
        frames[i] = -1;
    }

    // Traverse pages
    for(i = 0; i < n; ++i) {
        flag1 = flag2 = 0;
        
        // Check if page is already in frames
        for(j = 0; j < framesCount; ++j) {
            if(frames[j] == pages[i]) {
                counter++;
                //printf("\nCounter: %d",counter);
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        
        // Page not found in memory
        if(flag1 == 0) {
            for(j = 0; j < framesCount; ++j) {
                if(frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }
        
        // If no empty frame was found
        if(flag2 == 0) {
            pos = findLRU(time, framesCount);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }
        
        // Print current frames' status
        printf("\n");
        for(j = 0; j < framesCount; ++j) {
            if(frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }

        printf("\nTime:\n");
        for (int i=0;i<framesCount; i++){
            printf("T: %d\n", time[i]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", pageFaults);
}

int main() {
    int pages[30], framesCount, n, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter page reference sequence:\n");
    for(i = 0; i < n; ++i) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter number of frames: ");
    scanf("%d", &framesCount);
    
    LRU(pages, n, framesCount);
    
    return 0;
}
