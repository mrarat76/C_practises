#include <stdio.h>

int main() {
char input;
char charArray[100];

int index = 0;

printf("Enter characters, whe you code 'x' it will stop" );

while(1){

scanf("%c", &input);


if (input =='x'){
    break;
}
charArray[index]=input;

index++;

if(index>=100){

    printf("You reached the limit of array.");
    break;
}

}
 // Null-terminate the character array to make it a valid C string
    charArray[index] = '\0';
    
printf("Array content %s\n", charArray);


}