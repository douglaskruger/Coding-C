/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: simple_crc32.c$";

/*==============================================================================
  Description:
    Sample CRC32 from the internet.
   
    References: 
    https://docs.huihoo.com/doxygen/linux/kernel/3.7/crc16_8c.html
    https://www.lammertbies.nl/comm/info/crc-calculation
    https://www.linuxquestions.org/questions/linux-newbie-8/generate-crc-value-for-file-s-199640/
==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zlib.h>
#include <unistd.h>

int 
main(int argc, char *argv[])
{
    FILE *input_file;
    char *file_buffer;
    unsigned long file_size;
    unsigned long bytes_read;
    unsigned long crc;

    if (argc < 2)
    {
        printf("I need a filename to calculate crc on\n");
        return 1;
    }

    // Open the file to determine the size. This is used to size the malloc
    // later.
    input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 2;
    }
    fseek(input_file, 0, SEEK_END);
    file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    fclose(input_file);
    if (file_size == 0)
    {
        printf("File size is calculated to be 0. Cannot calculate CRC\n");
        return 3;
    }

    // Allocate the memory to read the file in.
    file_buffer = (char *)malloc(file_size);
    if (file_buffer == NULL)
    {
        printf("Unable to reserve enough memory for file buffer.\n");
        return 4;
    }

    int fd = open(argv[1], O_RDWR);
    bytes_read = read(fd, file_buffer, file_size);
    close(fd);

    if (bytes_read < file_size)
    {
        printf("Did not read entire contents of the file into buffer.\n");
        printf("  number of bytes read: %lu\n", bytes_read);
        free(file_buffer);
        return 5;
    }
    
    crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, (const unsigned char *)file_buffer, file_size);
    printf("Calculated CRC32: 0x%0lX\n", crc);
    free(file_buffer);

    return 0;
}
