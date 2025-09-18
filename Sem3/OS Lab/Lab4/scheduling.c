//Code referred from chatgpt and geeksforgeeks

#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].completion_time = time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        time = processes[i].completion_time;
    }
}

void display(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, 
               processes[i].burst_time, processes[i].completion_time, 
               processes[i].waiting_time, processes[i].turnaround_time);
    }
}

// First Come First Serve Scheduling
void FCFS(struct Process processes[], int n) {
    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    calculateTimes(processes, n);
    display(processes, n);
}

// Shortest Job First Scheduling
void SJF(struct Process processes[], int n) {
    // Sort by Arrival Time then Burst Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].burst_time > processes[j + 1].burst_time)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    calculateTimes(processes, n);
    display(processes, n);
}

// Priority Scheduling
void PriorityScheduling(struct Process processes[], int n) {
    // Sort by Priority then Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority ||
                (processes[j].priority == processes[j + 1].priority &&
                 processes[j].arrival_time > processes[j + 1].arrival_time)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    calculateTimes(processes, n);
    display(processes, n);
}

// Round Robin Scheduling
void RoundRobin(struct Process processes[], int n, int quantum) {
    int rem_burst_time[n];
    for (int i = 0; i < n; i++) 
        rem_burst_time[i] = processes[i].burst_time;

    int time = 0;
    bool done;
    do {
        done = true;
        for (int i = 0; i < n; i++) {
            if (rem_burst_time[i] > 0) {
                done = false;
                if (rem_burst_time[i] > quantum) {
                    time += quantum;
                    rem_burst_time[i] -= quantum;
                } else {
                    time += rem_burst_time[i];
                    rem_burst_time[i] = 0;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
    } while (!done);
    display(processes, n);
}

int main() {
    struct Process processes[] = {
        {1, 5, 2, 0}, {2, 6, 1, 0}, {3, 3, 0, 0}, {4, 5, 4, 0}, {5, 2, 5, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    int choice, quantum;
    printf("CPU Scheduling Algorithms:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Priority Scheduling\n");
    printf("4. Round Robin (4ms)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(processes, n);
            break;
        case 2:
            SJF(processes, n);
            break;
        case 3:
            for (int i = 0; i < n; i++) {
                printf("Enter priority for Process %d: ", processes[i].pid);
                scanf("%d", &processes[i].priority);
            }
            PriorityScheduling(processes, n);
            break;
        case 4:
            quantum = 4;
            RoundRobin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
