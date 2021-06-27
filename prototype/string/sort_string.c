/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: sort_string.c$";

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

int main() {
    int i;
    const char *input[] = {"a","orange","apple","mobile","car"};

    int stringLen = sizeof(input) / sizeof(char *);
    qsort(input, stringLen, sizeof(char *), myCompare);

    for (i=0; i<stringLen; ++i)
        printf("%d: %s\n", i, input[i]);
}
