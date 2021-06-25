/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: utc_time.c $";

/*==============================================================================
  Description:
   UTC Time sample
   http://zetcode.com/articles/cdatetime/
==============================================================================*/
#include <stdio.h> 
#include <time.h>     

int main(void) {
    
    time_t now = time(&now);
    
    if (now == -1) {
        
        puts("The time() function failed");
    }
        
    struct tm *ptm = gmtime(&now);
    if (ptm == NULL) 
    {
        printf("The gmtime() function failed");
    }    
    printf("UTC:   %s", asctime(ptm));

    ptm = localtime(&now);
    if (ptm == NULL) 
    {
        printf("The gmtime() function failed");
    }    
    printf("Local: %s", asctime(ptm));

    struct timespec curTime;
    struct tm curTm;
    clock_gettime(CLOCK_REALTIME, &curTime);
    gmtime_r(&curTime.tv_sec, &curTm);
    printf("UTC:   %04d-%02d-%02dT%02d:%02d:%02d.%03ldZ\n",
        curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
        curTm.tm_hour, curTm.tm_min, curTm.tm_sec, curTime.tv_nsec / 1000000);
    localtime_r(&curTime.tv_sec, &curTm);
    printf("Local: %04d-%02d-%02dT%02d:%02d:%02d.%03ld\n",
        curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
        curTm.tm_hour, curTm.tm_min, curTm.tm_sec, curTime.tv_nsec / 1000000);
    return 0;
}
