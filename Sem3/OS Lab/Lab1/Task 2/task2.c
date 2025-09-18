#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    char *filename = "student_info.txt";
    char name[100];
    char roll_no[100];
    char buffer[200];

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File does not exist. Please enter your details.\n");
        printf("Enter your name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        printf("Enter your roll number: ");
        fgets(roll_no, sizeof(roll_no), stdin);
        roll_no[strcspn(roll_no, "\n")] = '\0';

        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return EXIT_FAILURE;
        }

        fprintf(file, "Name: %s\nRoll No: %s\n", name, roll_no);
        fclose(file);

        printf("Details saved to file '%s'.\n", filename);
    } else {
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    return EXIT_SUCCESS;
}

