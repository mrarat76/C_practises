/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int no;
    char name[50];
} Student;

void write_students_to_file(const char *filename) {
    Student students[3] = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    fwrite(students, sizeof(Student), 3, file);
    fclose(file);
}

void read_students_from_file(const char *filename) {
    Student students[3];

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    fread(students, sizeof(Student), 3, file);
    for (int i = 0; i < 3; i++) {
        printf("No: %d, Name: %s\n", students[i].no, students[i].name);
    }

    fclose(file);
}

int main() {
    const char *filename = "students.bin";
    write_students_to_file(filename);
    read_students_from_file(filename);
    return 0;
}
