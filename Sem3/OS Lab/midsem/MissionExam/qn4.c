#include <stdio.h>
int main() {
    int n, i, j;
    n=4;

    int at[4]={0,0,0,0}, ct[n];
    int wt[n], tat[n],done[4]={0,0,0,0};
    int bt[4]={5,7,3,4};
    int t = 0, finish = 0, min_index;
    int process[4]={1,2,3,4};
    
     
    while (finish != n) {
        min_index = -1;
        int min_burst = 1000;
        for (i = 0; i < n; i++) {
            if  (at[i] <= t && !done[i]) {
                if (bt[i] < min_burst || (bt[i] == min_burst && at[i] < at[min_index])) {
                    min_burst = bt[i];
                    min_index = i;
                }
            }
        }
        
        if (min_index == -1) {
            t++;
            continue;
        }
    
        t += bt[min_index];
        ct[min_index] = t;
        tat[min_index] = ct[min_index] - at[min_index];
        wt[min_index] = tat[min_index] - bt[min_index];
        done[min_index] = 1;
        finish++;
    }
    
    printf("\n Pid \t AT \t BT \t CT \t WT \t TAT \n");
    for (i = 0; i < n; i++) {
        printf("%d \t %d \t %d \t %d \t %d \t %d \n", process[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }
    return 0;
}
