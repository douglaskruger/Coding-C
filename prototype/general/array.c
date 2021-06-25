/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: array.c$";

/*==============================================================================
  Description:
  Demo on printing arrays
==============================================================================*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <stdio.h>  
#include <stdlib.h>

void array_example1(void)
{
    printf("****************************************************************\n");
    printf("Exampele 1: Traversing a 2D array\n");
    int arr[4][3]={{1,2,3},{2,3,4},{3,4,5},{4,5,6}};     
    for(int i=0;i<4;i++)
    {    
        for(int j=0;j<3;j++)
        {    
            printf("2D Array - Address %p  ", &arr[i][j]);
            printf("array[%d][%d] = %d\n",i,j,arr[i][j]);    
        }
    }
}

void array_example2(void)
{
    printf("\n****************************************************************\n");
    printf("Example 2: Traversing a 3D array\n");
    int arr[2][2][3]={{{1,2,3},{2,3,4}},{{3,4,5},{4,5,6}}};     
    for(int i=0;i<2;i++)
    {    
        for(int j=0;j<2;j++)
        {    
            for(int k=0;k<3;k++)
            {    
                printf("3D Array - Address %p  ", &arr[i][j][k]);
                printf("arr[%d][%d][%d] = %d\n",i,j,k,arr[i][j][k]);    
            }
        }
    }    
}

void array_example3(void)
{
    printf("\n****************************************************************\n");
    printf("Example 3: Traversing a 2D array using a single pointer\n");
    int r = 3, c = 4; 
    int *arr = (int *)malloc(r * c * sizeof(int)); 
  
    int i, j, count = 0; 
    for (i = 0; i <  r; i++) 
        for (j = 0; j < c; j++) 
             *(arr + i*c + j) = ++count; 
  
    for (i = 0; i <  r; i++) 
        for (j = 0; j < c; j++) 
            printf("%d ", *(arr + i*c + j)); 
    free(arr);
}

void array_example4(void)
{
    printf("\n****************************************************************\n");
    printf("Example 4: Traversing a 2D array - using an array of pointers\n");
    int r = 3, c = 4, i, j, count; 
  
    int *arr[r]; 
    for (i=0; i<r; i++) 
         arr[i] = (int *)malloc(c * sizeof(int)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  r; i++) 
        for (j = 0; j < c; j++) 
            arr[i][j] = ++count; // Or *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  r; i++) 
        for (j = 0; j < c; j++) 
            printf("%d ", arr[i][j]); 
    for (i=0; i<r; i++) 
        free(arr[i]);
}

void array_example5(void)
{
    printf("\n****************************************************************\n");
    printf("Example 5: Traversing a 2D array - using a pointer to a pointer\n");
    int r = 3, c = 4, i, j, count; 
  
    int **arr = (int **)malloc(r * sizeof(int *)); 
    for (i=0; i<r; i++) 
        arr[i] = (int *)malloc(c * sizeof(int)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  r; i++) 
        for (j = 0; j < c; j++) 
            arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         printf("%d ", arr[i][j]); 
    for (i=0; i<r; i++) 
        free(arr[i]); 
    free(arr);
}

void array_example6(void)
{
    printf("\n****************************************************************\n");
    printf("Example 6: Traversing a 2D array - using a double pointer and single malloc\n");
    int r=3, c=4, len=0; 
    int *ptr, **arr; 
    int count = 0,i,j; 
  
    len = sizeof(int *) * r + sizeof(int) * c * r; 
    arr = (int **)malloc(len); 
  
    // ptr is now pointing to the first element in of 2D array 
    ptr = (int *)(arr + r); 
  
    // for loop to point rows pointer to appropriate location in 2D array 
    for(i = 0; i < r; i++) 
        arr[i] = (ptr + c * i); 
  
    for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            printf("%d ", arr[i][j]); 
    free(arr);
    printf("\n");
}

int 
main(int argc, char** argv)
{      
    array_example1();
    array_example2();
    array_example3();
    array_example4();
    array_example5();
    array_example6();
    return 0;  
}    
