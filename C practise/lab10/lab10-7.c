/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_string_in_file(const char *filename, const char *search_string) {
    char buffer[255];
    FILE *file;
    int line_number = 1;
    int found = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, search_string) != NULL) {
            printf("Found string '%s' on line %d\n", search_string, line_number);
            found = 1;
            break;
        }
        line_number++;
    }

    fclose(file);
    return found;
}

int main() {
    if (!search_string_in_file("test.txt", "search_term")) {
        printf("String not found.\n");
    }
    return 0;
}

