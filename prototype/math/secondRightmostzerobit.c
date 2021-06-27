/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: secondrightmostzerobit.c$";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

void print_binary(char * mystr, int n);
uint32_t calc(uint32_t n);

void
print_binary(char * mystr, int n)
{
    printf("String='%s', Value=%d ", mystr, n);
    for (int c = 31; c >= 0; c--)
    {
        int k = n >> c;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

uint32_t
calc(uint32_t n)
{
    uint32_t o=n;
    printf("Part 1\n");
    print_binary("n", n);
    print_binary("~n", ~n);
    print_binary("-~n", -~n);
    print_binary("~n&-~n", ~n&-~n);
    print_binary("n|(~n&-~n)", n|(~n&-~n));
    n |= ~n & -~n;
    printf("Part 2\n");
    print_binary("n", n);
    print_binary("~n", ~n);
    print_binary("-~n", -~n);
    print_binary("~n&-~n", ~n&-~n);
    n=o;
    return n |= ~n & -~n, ~n & -~n;
}

int
main()
{
    printf("calc() = %u\n\n", calc(4));
    printf("calc() = %u\n\n", calc(37));
}    
