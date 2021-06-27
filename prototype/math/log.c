/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: log.c$";

#include <stdio.h>
#include <math.h>

void calc(double num)
{
    double result = log10(num);
    printf("log(%.1f) = %.2f\n", num, result);
}

int main()
{
    calc(100);
    calc(102);
    calc(1000);
    calc(1002);
    calc(10000);
    calc(100000);
    return 0;
}
