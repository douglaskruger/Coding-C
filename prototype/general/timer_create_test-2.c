/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <time.h>

timer_t gTimerid;

static void
print_time()
{
    struct timespec     cur_time;
    struct tm           cur_time_tm;

    clock_gettime(CLOCK_REALTIME, &cur_time);
    gmtime_r(&(cur_time.tv_sec), &cur_time_tm);
    printf("Now = %04d-%02d-%02dT%02d:%02d:%02d.%06ldZ\n",
        cur_time_tm.tm_year + 1900, cur_time_tm.tm_mon + 1, cur_time_tm.tm_mday,
        cur_time_tm.tm_hour, cur_time_tm.tm_min, cur_time_tm.tm_sec,
        cur_time.tv_nsec / 1000000);
}

void start_timer(void)
{
    struct itimerspec value;

    // waits for 2 seconds before sending timer signal
    value.it_value.tv_sec = 2;
    value.it_value.tv_nsec = 0;

    // sends timer signal every 5 seconds
    value.it_interval.tv_sec = 5;
    value.it_interval.tv_nsec = 0;

    timer_settime(gTimerid, 0, &value, NULL);
}

void stop_timer(void)
{
    struct itimerspec value;

    // Set the values to zero, then set the timer
    value.it_value.tv_sec = 0;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_settime(gTimerid, 0, &value, NULL);
}

void timer_callback(int sig) 
{
    printf("Catched timer signal: %d … !!\n", sig);
    print_time();
}

int main(int ac, char **av)
{
    printf("Linux timer test - initial sleep 2 seconds with 5 second waits following\n");
    print_time();

    // Set the signal handler and then start the timer
    (void) signal(SIGALRM, timer_callback);

    // Create the timer
    timer_create(CLOCK_REALTIME, NULL, &gTimerid);

    // Start the timer
    start_timer();

    // while forever - note this eats the CPU - so only for demonstration purposes
    while(1);
}
