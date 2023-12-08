/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_line(const char *filename, int line_number) {
    FILE *file, *tempfile;
    char buffer[255];
    int count = 1;

    file = fopen(filename, "r");
    tempfile = fopen("tempfile.txt", "w");

    if (file == NULL || tempfile == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (count != line_number) {
            fputs(buffer, tempfile);
        }
        count++;
    }

    fclose(file);
    fclose(tempfile);
    remove(filename);
    rename("tempfile.txt", filename);
}

int main() {
    remove_line("test.txt", 2); // Example usage
    return 0;
}
