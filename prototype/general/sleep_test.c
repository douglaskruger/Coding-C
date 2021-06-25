/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void
print_time()
{
    struct timespec cur_time;
    struct tm       cur_time_tm;

    clock_gettime(CLOCK_REALTIME, &cur_time);
    gmtime_r(&(cur_time.tv_sec), &cur_time_tm);
    printf("Time: %04d-%02d-%02dT%02d:%02d:%02d.%03ldZ\n",
        cur_time_tm.tm_year + 1900, cur_time_tm.tm_mon + 1, cur_time_tm.tm_mday,
        cur_time_tm.tm_hour, cur_time_tm.tm_min, cur_time_tm.tm_sec,
        cur_time.tv_nsec / 1000000);
}

int main()
{
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;

    printf("Nano Sleep - nanosleep() 1 second\n");
    print_time();
    if(nanosleep(&tim , &tim2) < 0 )   
    {
        printf("Nano sleep system call failed \n");
        return -1;
    }
    print_time();

    printf("\nMicro sleep - usleep() - 1 second\n");
    print_time();
    usleep(1000000);
    print_time();

    printf("\nsleep - sleep() 1 second\n");
    print_time();
    sleep(1);
    print_time();

    return 0;
}
