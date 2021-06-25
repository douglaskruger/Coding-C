/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: timer_example3.c $";

/*==============================================================================
  Description:
    Timer sample

  Reference: 
	man page
==============================================================================*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

timer_t firstTimerID;
timer_t secondTimerID;
timer_t thirdTimerID;
timer_t fourthTimerID;

static void timerHandler( int sig, siginfo_t *si, void *uc );

static int
makeTimer( char *name, timer_t *timerID, int expireMS, int intervalMS )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sigNo = SIGRTMIN;

    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sigNo, &sa, NULL) == -1)
    {
        fprintf(stderr, "%s: Failed to setup signal handling for %s.\n", "timer_example3", name);
        return(-1);
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = intervalMS * 1000000;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expireMS * 1000000;
    timer_settime(*timerID, 0, &its, NULL);

    return(0);
}

void
print_time()
{
#define tzTIMESPEC struct timespec
#define tzTIME_TM struct tm

    struct tm       curTm;
    tzTIMESPEC      now;

	clock_gettime(CLOCK_REALTIME, &now);
	gmtime_r(&(now.tv_sec), &curTm);
	printf("Time is: %04d-%02d-%02dT%02d:%02d:%02d.%03ldZ\n",
	curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
	curTm.tm_hour, curTm.tm_min, curTm.tm_sec, now.tv_nsec / 1000000);
}

void
firstCB(int sig, siginfo_t *si, void *uc )
{
	printf("First Timer - 1ms ");
	print_time();
}

void
secondCB(int sig, siginfo_t *si, void *uc )
{
	printf("Second Timer - 10ms ");
	print_time();
}

void
thirdCB(int sig, siginfo_t *si, void *uc )
{
	printf("Third Timer -50ms ");
	print_time();
}

void
fourthCB(int sig, siginfo_t *si, void *uc )
{
	printf("Fourth Timer -100ms ");
	print_time();
}

static void
timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    if ( *tidp == firstTimerID )
        firstCB(sig, si, uc);
    else if ( *tidp == secondTimerID )
        secondCB(sig, si, uc);
    else if ( *tidp == thirdTimerID )
        thirdCB(sig, si, uc);
    else if ( *tidp == fourthTimerID )
        fourthCB(sig, si, uc);
}

int
main( void )
{
    int rc;
    rc = makeTimer("First Timer", &firstTimerID, 1, 1);
    rc = makeTimer("Second Timer", &secondTimerID, 10, 10);
    rc = makeTimer("Third Timer", &thirdTimerID, 50, 50);
    rc = makeTimer("Fourth Timer", &fourthTimerID, 100, 100);
	
	while(1)
	{
		pause();
	}
    return rc;
}
