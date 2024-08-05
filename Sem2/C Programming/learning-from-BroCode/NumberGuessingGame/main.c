#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int main()
{
    const int MIN = 1;
    const int MAX = 100;
    int guess;
    int guesses = 0; 
    int answer; 

    // uses the current time as a seed
    srand(time(0));

    // generate a random number between MIN & MAX
    answer = (rand() % MAX) + MIN;

    do
    {
        printf("Enter a guess: ");
        scanf("%d", &guess);

        if(guess > answer)
        {
            printf("Too high!\n");
        }

        else if(guess < answer)
        {   
            printf("Too low!\n");
        }

        else
        {
            printf("CORRECT!\n");
        }

        guesses++;

    } while (guess != answer);
    
    printf("\n");
    printf("Answer: %d\n", answer);
    printf("Guesses: %d\n", guesses);

    return 0;
}