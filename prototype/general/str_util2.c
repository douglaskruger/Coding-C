/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include<stdio.h>

int main() {
    char* buffer = "Hello 20 23,4";
    char store_string[10];
    int store_integer;
    int total_read;
    float store_float;

    total_read = sscanf(buffer, "%s %d %f" , store_string, &store_integer, &store_float);

    printf("String value in buffer: %s" ,store_string);
    printf(" \nInteger value in buffer: %d",store_integer);
    printf(" \nFloat value in buffer: %f",store_float);
    printf("\nTotal items read: %d\n",total_read);
    return 0;
}
