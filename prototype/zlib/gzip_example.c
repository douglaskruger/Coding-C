/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: archive_dump.c$";

/*==============================================================================
  Description:

   The following is the Real Time Database dump routines. These library calls
   are available to load and dump the database.

==============================================================================*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <sys/stat.h>
#include <fcntl.h>
#include <zlib.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    char buffer[] = "This is my story.... It was a dark and stormy night";
    char basepath[] = "/home/parallels/msm";
    char path1 [100];
    char path2 [100];

    uint32_t counter=0;
    while (counter++ < 10)
    {
        sprintf(path1, "%s/file_%d.txt", basepath, counter);
        sprintf(path2, "%s/file_%d.txt.gz", basepath, counter);
        int32_t file_des = open(path1, O_CREAT | O_WRONLY, 0666);
        if (file_des < 0)
        {
            printf("Failed to open");
        }

        gzFile fi = gzopen(path2, "wb");
        if (fi == NULL)
        {
            printf("Failed to open");
        }
        uint32_t loop = 0;
        while (loop++ < 100)
        {
            uint32_t bytes_wrote = gzwrite(fi, buffer, strlen(buffer));
            printf("File: %s Wrote Bytes (gzip) = %u\n", path1, bytes_wrote);
            bytes_wrote = write(file_des, buffer, strlen(buffer));
            printf("File: %s Wrote Bytes (normal) = %u\n", path2, bytes_wrote);
        }
        gzclose(fi);
        close(file_des);
    }
}
