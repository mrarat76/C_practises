#include <stdio.h>
int input;
int main(){
    
    printf("Write a number");
    scanf("%d", &input);
    if(input %2 == 0){
        printf("This number is prime");
    } else {
        printf("This is not a prime number");
    }
   


}