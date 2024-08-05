#include <stdio.h> 
#include <strings.h> 

int main()
{
    // while loop = repeats a block of code possibly infinite times. 
    // it executes a block of code WHILE some condition remains true
    // a while loop might not execute at all

    char name[25];

    printf("\nWhat's your name?: ");
    fgets(name, 25, stdin);

    name[strlen(name) - 1] = '\0';

    while(strlen(name) == 0)
    {
        printf("You did not enter your name");
        printf("\nWhat's your name?: ");
        fgets(name, 25, stdin);

        name[strlen(name) - 1] = '\0';
    }

    printf("Hello %s", name);

    return 0;
}