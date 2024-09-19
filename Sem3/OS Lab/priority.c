#include <stdio.h>

#define MAX 100

int main() {
    int n;
    int at[MAX], bt[MAX], pr[MAX], ct[MAX], wt[MAX], tat[MAX], rt[MAX];
    int completed = 0, t = 0, min_pr, shortest;
    float total_wt = 0, total_tat = 0;
    int is_completed[MAX] = {0};

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time, Burst Time and Priority of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    while (completed != n) {
        min_pr = 10000;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= t && is_completed[i] == 0) {
                if (pr[i] < min_pr) {
                    min_pr = pr[i];
                    shortest = i;
                }
                if (pr[i] == min_pr) {
                    if (at[i] < at[shortest]) {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1) {
            t++;
        } else {
            rt[shortest]--;
            t++;

            if (rt[shortest] == 0) {
                completed++;
                is_completed[shortest] = 1;
                ct[shortest] = t;
                tat[shortest] = ct[shortest] - at[shortest];
                wt[shortest] = tat[shortest] - bt[shortest];

                total_wt += wt[shortest];
                total_tat += tat[shortest];
            }
        }
    }

    printf("\nProcess\tAT\tBT\tP\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
