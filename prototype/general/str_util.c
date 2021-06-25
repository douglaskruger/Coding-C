/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: str_util.c$";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Source: strtok man page

    An example of the output produced by this program is the following:

       $ ./a.out 'a/bbb///cc;xxx:yyy:' ':;' '/'
       1: a/bbb///cc
                --> a
                --> bbb
                --> cc
       2: xxx
                --> xxx
       3: yyy
                --> yyy
*/

int
main(int argc, char *argv[])
{
    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j, count=0;;
    int val_low=-1; 
    int val_high=-1;

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        fprintf(stderr, "  tokens are '-' and '[]'\n");
        fprintf(stderr, "Example: %s [3-5]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) 
    {
        token = strtok_r(str1, "-", &saveptr1);
        if (token == NULL)
        break;

        for (str2 = token; ; str2 = NULL) 
        {
            subtoken = strtok_r(str2, "[]", &saveptr2);
            if (subtoken == NULL)
                break;
            if (strcmp(subtoken, "all") == 0)
            {
                val_low = -1;
                val_high = -1;
                break;
            }

        if (count++ == 0)
            val_low = strtol(subtoken, NULL, 0);
        else
            val_high = strtol(subtoken, NULL, 0);
        }
    }
    printf("low=%d, high=%d\n", val_low, val_high);

    exit(EXIT_SUCCESS);
}
