/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: uptime_example.c $";

/*==============================================================================
  Description:
    print out the uptime
==============================================================================*/
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#if defined(CLOCK_BOOTTIME)
	#define UPTIME_FLAG CLOCK_BOOTTIME
#elif defined(CLOCK_UPTIME)
	#define UPTIME_FLAG CLOCK_UPTIME
#else
	#define UPTIME_FLAG CLOCK_MONOTONIC
#endif

int main(void)
{
	char warn_buf[256];
	struct timespec uptime;

	if (clock_gettime(UPTIME_FLAG, &uptime) < 0) 
    {
		snprintf(warn_buf, 256, "clock_gettime %d", UPTIME_FLAG);
		return 1;
	}

    uintmax_t d = uptime.tv_sec / 86400;
    uintmax_t h = (uptime.tv_sec / 3600) % 24;
    uintmax_t m = (uptime.tv_sec % 3600) / 60;
    uintmax_t s = uptime.tv_sec % 60;

    printf("Raw: %lu    Uptime: %jud %02juh %02jum %02jus\n\n", uptime.tv_sec, d, h, m, s);
    return 0;
}
