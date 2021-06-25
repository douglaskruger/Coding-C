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
#include <stdlib.h>

int main()
{
    float myFloatValue=4123.3;
    for (int i=0; i< 10; i++)
    {
        printf("Width:%u, Precision:%u, %*.*f\n", i+2, i, i+2, i, myFloatValue);
        printf("Precision:%u, %.*f\n", i, i, myFloatValue);
    }
}
