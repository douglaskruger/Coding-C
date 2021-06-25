/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: endian.c$";

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 16-Bit Big Endian
#define SWAP_BYTES_AB(A)   (A)
// 16-Bit Little Endian
#define SWAP_BYTES_BA(A)   (A>>8)|(A<<8)

// 32-Bit Big Endian
#define SWAP_BYTES_ABCD(A) (A)
// 32-Bit Big Endian + SWAP_BYTES bytes
#define SWAP_BYTES_BADC(A) ((A>>8)&0xff0000) | ((A<<8)&0xff000000) | ((A<<8)&0xff00) | ((A>>8)&0xff)
// 32-Bit Little Endian + Swap bytes
#define SWAP_BYTES_CDAB(A) ((A>>16)&0xff00) | ((A>>16)&0xff) | ((A<<16)&0xff000000) | ((A<<16)&0xff0000)
// 32-Bit Little Endian
#define SWAP_BYTES_DCBA(A) ((A>>24)&0xff) | ((A<<8)&0xff0000) | ((A>>8)&0xff00) | ((A<<24)&0xff000000)

int main()
{
    uint16_t  num_16;
    uint32_t  num_32;

    printf("\n16 Bit\n");

    num_16 = 0xAABB;
    num_16 = SWAP_BYTES_AB(num_16);
    printf("AB   Number=0x%04X (%05u)\n", num_16, num_16);

    num_16 = 0xAABB;
    num_16 = SWAP_BYTES_BA(num_16);
    printf("BA   Number=0x%04X (%05u)\n", num_16, num_16);



    printf("\n32 Bit\n");
    
    num_32 = 0xFEA01204;
    num_32 = SWAP_BYTES_ABCD(num_32);
    printf("ABCD Number=0x%08X (%010u)\n", num_32, num_32);

    num_32 = 0xFEA01204;
    num_32 = SWAP_BYTES_BADC(num_32);
    printf("BADC Number=0x%08X (%010u)\n", num_32, num_32);

    num_32 = 0xFEA01204;
    num_32 = SWAP_BYTES_CDAB(num_32);
    printf("CDAB Number=0x%08X (%010u)\n", num_32, num_32);

    num_32 = 0xFEA01204;
    num_32 = SWAP_BYTES_DCBA(num_32);
    printf("DCBA Number=0x%08X (%010u)\n", num_32, num_32);
}
