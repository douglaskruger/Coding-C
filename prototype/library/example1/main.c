/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>
#include "sum.h"

int main(void)
{
    int x = 5;
    int y = 8;
    printf("The sum of %d + %d = %d\n", x, y, sum(x,y));
    return (0);
}
