#include <stdio.h>

#define MAX_PROCESSES 4

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate times for FCFS scheduling
void calculateTimes(struct Process processes[], int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // If current time is less than arrival time, update current time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Calculate completion time
        processes[i].completion_time = current_time + processes[i].burst_time;

        // Calculate turnaround time
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        // Calculate waiting time
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        // Update current time
        current_time = processes[i].completion_time;
    }
}

// Function to display the process details
void displayProcesses(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].id, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].completion_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time);
    }
}

int main() {
    struct Process processes[MAX_PROCESSES] = {
        {1, 2, 5},
        {2, 1, 6},
        {3, 0, 3},
        {4, 4, 5}
    };

    // Calculate times
    calculateTimes(processes, MAX_PROCESSES);

    // Display results
    displayProcesses(processes, MAX_PROCESSES);
    
    // Calculate and display average waiting time and turnaround time
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= MAX_PROCESSES;
    avg_turnaround_time /= MAX_PROCESSES;

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
    
}