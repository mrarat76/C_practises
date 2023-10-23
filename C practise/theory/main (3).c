/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void allocator(int **ptrTempAllctr) {
    *ptrTempAllctr = malloc(sizeof(int));
    if (*ptrTempAllctr == NULL) {
        printf("Memory allocation error in allocator()\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Memory allocation successful\n");
    }
}

int main() {
    int *p = NULL;
    allocator(&p);

    if (p == NULL) {
        printf("p contains NULL\n");
    }

    return 0;
}