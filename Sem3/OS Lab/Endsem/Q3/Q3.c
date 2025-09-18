#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter the number of people to use the workstation: ");
    scanf("%d", &n);

    int arrival_time[n], time_req[n], completion_time[n];
    int waiting_time[n], turnaround_time[n], person[n];
    int is_completed[n];
    
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and time taken(in hours) by person %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &time_req[i]);
        person[i] = i + 1;
        is_completed[i] = 0;
    }
    
    int time = 0, completed = 0, min_index;
    
    while (completed != n) {
        min_index = -1;
        int min_burst = 1000000;
        
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && !is_completed[i]) {
                if (time_req[i] < min_burst || (time_req[i] == min_burst && arrival_time[i] < arrival_time[min_index])) {
                    min_burst = time_req[i];
                    min_index = i;
                }
            }
        }
        
        
        if (min_index == -1) {
            time++;
            continue;
        }
        
        
        time += time_req[min_index];
        completion_time[min_index] = time;
        turnaround_time[min_index] = completion_time[min_index] - arrival_time[min_index];
        waiting_time[min_index] = turnaround_time[min_index] - time_req[min_index];
        is_completed[min_index] = 1;
        completed++;
    }
    
    printf("\nPerson\tArrival Time\tTime Required\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", person[i], arrival_time[i], time_req[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    return 0;
}
