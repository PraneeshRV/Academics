#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], completion_time[n];
    int waiting_time[n], turnaround_time[n], process[n];
    int is_completed[n];
    
    // Input arrival time and burst time
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        process[i] = i + 1;
        is_completed[i] = 0; // Mark all processes as not completed
    }
    
    int time = 0, completed = 0, min_index;
    
    while (completed != n) {
        min_index = -1;
        int min_burst = 1000000; // Assign a large number to compare with
        
        // Find the process with the shortest burst time among the arrived processes
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && !is_completed[i]) {
                if (burst_time[i] < min_burst || (burst_time[i] == min_burst && arrival_time[i] < arrival_time[min_index])) {
                    min_burst = burst_time[i];
                    min_index = i;
                }
            }
        }
        
        // If no process is found, increment time
        if (min_index == -1) {
            time++;
            continue;
        }
        
        // Process execution
        time += burst_time[min_index];
        completion_time[min_index] = time;
        turnaround_time[min_index] = completion_time[min_index] - arrival_time[min_index];
        waiting_time[min_index] = turnaround_time[min_index] - burst_time[min_index];
        is_completed[min_index] = 1;
        completed++;
    }
    
    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    return 0;
}
