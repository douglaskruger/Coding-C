/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: permutation.c$";

#include <stdio.h>
#include <string.h>

int counter=0;
 
// Function to swap values at two pointers
void swap_char(char *x, char *y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}
 
// Function to print permutations of string
//   This function takes three parameters: 
//   1. String
//   2. Starting index of the string
//   3. Ending index of the string
void permute(char *a, int l, int r)
{
    if (l == r)
    {
        counter++;
        printf("%s\n", a);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap_char((a+l), (a+i));
            permute(a, l+1, r);
            swap_char((a+l), (a+i));
        }
    }
}
 
// Main Function
int main()
{
    char str[] = "ABCD";
    int n = strlen(str);
    permute(str, 0, n-1);
    printf("Total Permutations=%d\n", counter);
    return 0;
}
