/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: math_test.c$";

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    uint16_t scale = 10;
    uint16_t offset = 5;
    double  temp;

    uint8_t  i8 = 2;
    uint16_t i16 = 3369;
    uint32_t i32 = 72000;

    // Print initial values
    printf("\n");
    printf("Value uint8_t=%u, uint16_t=%u, uint32_t=%u\n", i8, i16, i32);
    printf("Scale uint16_t=%u, Offset uint16_t=%u\n", scale, offset);
    printf("Value = Value*scale + offset\n");

    temp = i8 * scale + offset;
    i8 = (uint8_t) temp;
    temp = i16 * scale + offset;
    i16 = (uint16_t) temp;
    temp = i32 * scale + offset;
    i32 = (uint32_t) temp;
    printf("Results uint8_t=%u, uint16_t=%u, uint32_t=%u\n", i8, i16, i32);

    int val_i = 10;
    float val_f = 20.2;
    double val_d = 30.3;

    printf("\n");
    printf("Value = Value*scale + offset\n");
    printf("Scale uint16_t=%u, Offset uint16_t=%u\n", scale, offset);
    printf("Value (int)   = %d Result=%d\n", val_i, val_i*scale+offset);
    printf("Value (float) = %f Result=%f\n", val_f, val_f*scale+offset);
    printf("Value (double)= %f Result=%f\n", val_d, val_d*scale+offset);
    val_i = val_f*scale+offset;
    printf("Value (int)   = %d Result=%d\n", val_i, val_i*scale+offset);
    printf("\n");
    return 1;
}
