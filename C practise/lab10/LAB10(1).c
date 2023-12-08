/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int main()
{
    int rows;
    int columns;
    
    scanf("%d %d\n", &rows,&columns);
    
    int** matrix= (int**)malloc(rows* sizeof(int*));
    for(int i=0; i<rows; i++){
        matrix[i]= (int*)malloc(columns*sizeof(int);
    }
    
      printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
        
        int **transpose= (int**) malloc(columns* sizeof(int*));
        for(int i=0; i<columns; i++){
            transpose[i]=(int*) malloc(rows* sizeof(int*));
            
        }
}
