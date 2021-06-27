/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: matchbit.c$";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <strings.h>

void print_binary(char * mystr, int n);
uint32_t calc(uint32_t n, uint32_t m);

void
print_binary(char * mystr, int n)
{
    printf("String='%-18s', Value=%010u  Bin=", mystr, n);
    for (int c = 31; c >= 0; c--)
    {
        int k = n >> c;
        if (k & 1)
            printf("1");
        else
            printf("0");
        if (c%4 == 0)
            printf(" ");
    }
    printf("  Hex=0x%08x\n", n);
}

uint32_t
calc(uint32_t n, uint32_t m)
{
    print_binary("n", n);
    print_binary("m", m);
    print_binary("n^m", n^m);
    print_binary("n^m+1", n^m+1);
    print_binary("~(n^m)", ~(n^m));
    return ~(n^m) & ((n^m)+1);
}

int
main()
{
    printf("calc() = %u\n\n", calc(10,11));
    printf("calc() = %u\n\n", calc(0,0));
    printf("calc() = %u\n\n", calc(28,27));
    printf("calc() = %u\n\n", calc(895,928));
    printf("calc() = %u\n\n", calc(1073741824,1006895103));
}
