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
#include <locale.h>

int main(void)
{
    setlocale(LC_NUMERIC, "");
    printf("%'d\n", 1123456789);
    return 0;
}
