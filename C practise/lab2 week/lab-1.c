
#include <stdio.h>

int sizeofif(int a, float b){
    int size = a+b;
    
    return sizeof(size);
}

int sizroffd(float b, double c){
    
  int size = b+c;
  
  return sizeof(size);

}



int main()
{
    int a;
    float b;
    double c;
    
    scanf("%d %f %lf", &a, &b,&c);
    
    
    printf("The size of a plus b: %d\n", sizeofif(a,b));
    printf("The size of b plus c: %d\n", sizeof(b,c));

    return 0;
}
