#include <stdio.h>
#include <string.h> 

int main()
{
    char name[25];  //bytes
    int age;

    printf("\nWhat's your name? ");
    //scanf("%s", &name); // used to get input from the user 
    fgets(name, 25, stdin);  // fgets(variable, input size, stdin); used to get input with whitespaces
    name[strlen(name)-1] = '\0';  
    // gets rid of newline character present by default in input using fgets (string formatting)


    printf("How old are you? ");
    scanf("%d", &age); // scanf reads input till the first whitespace

    printf("\nHello %s, how are you?", name);
    printf("\nYou are %d years old", age);


    return 0;
}