#include <stdio.h>

void prntarr(int *arry){

int sizet;

sizet = sizeof(arry)/ sizeof(arry[0]);

for(int i = 0; i< sizet; i++){

    printf("%d\n", arry[i]);
}


}





int main(){
int arry[]= {1,2,3,4,5};
int sayi;





prntarr(arry);

    return 0;
}