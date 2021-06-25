/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: prt_test.c$";

#include <stdio.h>

void
inc_counter(int * num_ptr)
{
    printf("Num=%u\n", *num_ptr);
    (*num_ptr)++;
    printf("Num2=%u\n", *num_ptr);
}

int 
main (int argc, char *argv[])
{
    for (int counter = 0; counter < 10; counter++)
    {
        printf("Counter=%u\n", counter);
        inc_counter(&counter);
    }
    return 0;
}
