#include <stdio.h>

int main() {
    int num, sum = 0;

    printf("Enter numbers (enter -1 to exit):\n");
    
    while (1) {
        scanf("%d", &num); 

        if (num == -1) {
            break; 
        }

        sum += num;
    }

    printf("Sum of entered values: %d\n", sum);

    return 0;
}
