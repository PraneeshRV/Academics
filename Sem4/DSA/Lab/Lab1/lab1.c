#include <stdio.h>

int main() {
    int marks[100];
    int count[86] = {0};
    int n, i;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    printf("Enter the marks obtained by students (30-85):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &marks[i]);
        if (marks[i] >= 30 && marks[i] <= 85) {
            count[marks[i]]++;
        }
        else {
            printf("Invalid marks, marks should be between 30 and 85 \n ");
            i--;
        }
    }

    printf("Students with same marks:\n");
    for (i = 30; i <= 85; i++) {
        if (count[i] > 1) {
            printf("Number of students with %d Marks: %d students\n", i, count[i]);
        }
    }

    return 0;
}
