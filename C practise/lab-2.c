#include <stdio.h>

int main() {
    char char1, char2, char3;
    
    
    printf("Enter the first character: ");
    scanf(" %c", &char1);  
    
    printf("Enter the second character: ");
    scanf(" %c", &char2);
    
    printf("Enter the third character: ");
    scanf(" %c", &char3);
    
    char highest_char;
    if (char1 >= char2 && char1 >= char3) {
        highest_char = char1;
    } else if (char2 >= char1 && char2 >= char3) {
        highest_char = char2;
    } else {
        highest_char = char3;
    }
    
    printf("The character with the highest ASCII value is: %c\n", highest_char);
    
    return 0;
}


    