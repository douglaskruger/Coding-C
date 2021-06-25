/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>
int main()
{
    FILE *cmd=popen("ls", "r");
    char result[24]={0x0};
    while (fgets(result, sizeof(result), cmd) !=NULL)
        printf("%s", result);
    pclose(cmd);
    return 0;
}
