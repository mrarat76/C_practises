/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[255];
    FILE *file;

    printf("Enter the text you want to store in the file: ");
    fgets(input, sizeof(input), stdin); // Read user input

    file = fopen("output.txt", "w"); // Open the file in write mode
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    fprintf(file, "%s", input); // Write input to the file
    fclose(file); // Close the file

    printf("Input has been written to output.txt\n");

    return 0;
}
