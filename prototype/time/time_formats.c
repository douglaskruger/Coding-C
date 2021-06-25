/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: time_formats.c $";

/*==============================================================================
  Description:
   Time sample 

   Tips from: http://zetcode.com/articles/cdatetime/
==============================================================================*/
#include <stdio.h> 
#include <time.h>        
#include <string.h>

#define BUF_LEN 256

int main(void) {
    
    char buf[BUF_LEN] = {0};
    
    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
        return 1;   
    }
    
    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
        
        puts("The localtime() function failed");
        return 1;
    }

    strftime(buf, BUF_LEN, "Today is %A", ptm);
    puts(buf);
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "The month is %B", ptm);
    puts(buf);
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "Today is %-d day of %B", ptm);
    puts(buf);

    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "Today is %-j day of %G", ptm);
    puts(buf);    
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "Today is %-W week of %G", ptm);
    puts(buf);        
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "The time is %T", ptm);
    puts(buf);     
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "The date is %D", ptm);
    puts(buf);       
    
    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "The timezone is %Z", ptm);
    puts(buf);       

    return 0;
}
