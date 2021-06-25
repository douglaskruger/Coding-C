/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>
#include <unistd.h>

int
main()
{
    // Do forever
    while (1)
    {
        char char1 = getchar();
        printf("Char=%c, %d\n", char1, char1);
    }
}
