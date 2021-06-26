/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: read_file.c$";

#include <stdio.h>
#include <string.h>

int main()
{
    FILE * database;
    char buffer [1024];

    database = fopen("test.csv","r");

    if (NULL == database) {
        perror("opening database file");
        return (-1);
    }

    // while not end-of-file
    int i=0;
    while (!feof(database)) { 

        // we expect buffer pointer back if all is well, get out if we don't get it 
        if (buffer != fgets(buffer, sizeof(buffer)-1, database))
            break;

        // strip /n
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
            buffer[len - 1] = 0;

        printf("Data(%.3d): %s\n", i, buffer); 
        if (i++ > 20)
            break;
    }

    // a little clean-up
    fclose(database);

    return (0);
}
