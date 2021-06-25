/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/

/*==============================================================================
  Description:
    Prototype string functions
==============================================================================*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <stdio.h>
    
void showbits( unsigned int x )
{
    for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int main( void )
{
    int j = 5225;
    printf("%d in binary \t\t ", j);

    // assume we have a function that prints a binary string when given decimal integer 
    showbits(j);

    /* the loop for right shift operation */
    for (int m = 0; m <= 5; m++)
    {
        int n = j >> m;
        printf("%d right shift %d gives ", j, m);
        showbits(n);
    }
    return 0;
}
