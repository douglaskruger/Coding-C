/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: c_datatype.c$";

#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

int main()
{
    printf("\n");
    printf("C Compiler Data Types - Sizes, Min/Max Values\n");
    printf("\nSee: https://en.wikipedia.org/wiki/C_data_types\n\n");

    printf("bool               = %lu bytes\n", sizeof(bool));

    printf("char               = %lu bytes, min=%d max=%d\n", sizeof(char), SCHAR_MIN,SCHAR_MAX);
    printf("short              = %lu bytes, min=%d max=%d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("int                = %lu bytes, min=%d max=%d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("long               = %lu bytes, min=%ld max=%ld\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("long long          = %lu bytes, min=%lld max=%lld\n", sizeof(long long), LLONG_MIN, LLONG_MAX);

    printf("unsigned char      = %lu bytes, min=%u max=%u\n", sizeof(char), 0, UCHAR_MAX);
    printf("unsigned short     = %lu bytes, min=%u max=%u\n", sizeof(short), 0, USHRT_MAX);
    printf("unsigned int       = %lu bytes, min=%u max=%u\n", sizeof(int), 0, UINT_MAX);
    printf("unsigned long      = %lu bytes, min=%u max=%lu\n", sizeof(long), 0, ULONG_MAX);
    printf("unsigned long long = %lu bytes, min=%u max=%llu\n", sizeof(long long), 0, ULLONG_MAX);

    printf("float              = %lu bytes, min=%f max=%f\n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("double             = %lu bytes, min=%f max=%f\n", sizeof(double), DBL_MIN, DBL_MAX);
    printf("ssize_t            = %lu bytes\n", sizeof(ssize_t));
    printf("time_t             = %lu bytes\n", sizeof(time_t));
    printf("caddr_t            = %lu bytes\n", sizeof(caddr_t));
    printf("struct timespec    = %lu bytes\n", sizeof(struct timespec));

    printf("\nSee limits.h for system limitations.\n");
    printf("\n gcc compiler flags:.\n");
    printf("-m32  generates 32 bit code\n");
    printf("-mx32 generates 64 bit code with 32 bit longs and pointers\n");
    printf("-m64  generates 64 bit code\n");
    return 1;
}
