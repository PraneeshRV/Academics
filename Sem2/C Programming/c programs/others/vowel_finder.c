#include <stdio.h>

void main()
{
    char letter; 
    int ascii_val; 

    printf("Enter character: ");
    scanf("%c", &letter);

    ascii_val = (int) letter;

    if(ascii_val >= 97 && ascii_val <= 122)
    {
        ascii_val -= 32;
        switch(ascii_val)
        {
            case 65:
            {
                printf("Vowel");
                break;
            }

            case 69:
            {
                printf("Vowel");
                break;
            }

            case 73:
            {
                printf("Vowel");
                break;
            }

            case 79:
            {
                printf("Vowel");
                break;
            }

            case 85:
            {
                printf("Vowel");
                break;
            }

            default:
                printf("Consonant");
            
        }

    }

    else if(ascii_val >= 65 && ascii_val <= 90)
    {
        switch(ascii_val)
        {
            case 65:
            {
                printf("Vowel");
                break;
            }

            case 69:
            {
                printf("Vowel");
                break;
            }

            case 73:
            {
                printf("Vowel");
                break;
            }

            case 79:
            {
                printf("Vowel");
                break;
            }

            case 85:
            {
                printf("Vowel");
                break;
            }

            default:
                printf("Consonant");
        }
    }

    else
    {
        printf("Not a letter!");
    }


}