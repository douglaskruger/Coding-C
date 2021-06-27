/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: rightmostdiffbit.c$";

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
calc(uint32_t n, uint32_t m)
{
    uint32_t o=n;
    print_binary("n", n);
    print_binary("m", m);
    print_binary("n^m", n^m);
    print_binary("ffs(n^m)", ffs(n^m));
    print_binary("1<<(ffs(n^m)-1)", 1<<(ffs(n^m)-1));
    return 1<<(ffs(n^m)-1);
}

int
main()
{
    printf("calc() = %u\n\n", calc(11,13));
    printf("calc() = %u\n\n", calc(7,23));
    printf("calc() = %u\n\n", calc(1073741823,1071513599));
}    
