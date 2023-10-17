#include <stdio.h>
#include "lab-4.h"

int main() {
    printf("Initial globalVariable value: %d\n", globalVariable);

    // Modify the globalVariable from the modifyGlobalVariable function
    modifyGlobalVariable(42);
    printf("Updated globalVariable value: %d\n", globalVariable);

    // Modify the globalVariable from main
    globalVariable = 17;
    printf("Updated globalVariable value from main: %d\n", globalVariable);

    return 0;
}
