#include <stdio.h> 

int main()
{
    
    FILE *pF = fopen("test.txt", "w");

    fprintf(pF, "Spongebob Squarepants");

    fclose(pF);
    
    
    /*  
    if(remove("test.txt") == 0)
    {
        printf("That file was deleted successfully!");
    }

    else
    {
        printf("That file was NOT deleted!");
    }
    */

    return 0;
}