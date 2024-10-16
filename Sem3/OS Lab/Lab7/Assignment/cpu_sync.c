#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROLL_NUMBER 36

int num;  
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
void* check_prime(void* arg) {
    if (is_prime(num)) {
        printf("%d is prime.\n", num);
        num += ROLL_NUMBER;
        printf("Updated number (after adding rollno. (36)): %d\n", num);
    } else {
        printf("%d is not prime.\n", num);
        num -= ROLL_NUMBER;
        printf("Updated number (after subtracting rollno. (36)): %d\n", num);
    }
    return NULL;
}
void* display_range(void* arg) {
    int random_num;
    srand(time(0));
    random_num = (rand() % 90) + 10;  
    printf("Random number generated: %d\n", random_num);
    
    printf("Numbers between %d and %d:\n", random_num, num);
    if (random_num < num) {
        for (int i = random_num + 1; i < num; i++) {
            printf("%d ", i);
        }
    } else {
        for (int i = num + 1; i < random_num; i++) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return NULL;
}
int main() {
    pthread_t thread1, thread2;
    printf("Enter a number: ");
    scanf("%d", &num);
    pthread_create(&thread1, NULL, check_prime, NULL);
    pthread_create(&thread2, NULL, display_range, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}