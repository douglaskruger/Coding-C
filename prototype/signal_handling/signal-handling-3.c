/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>     /* standard I/O functions                         */
#include <unistd.h>    /* standard unix functions, like getpid()         */
#include <signal.h>    /* signal name macros, and the signal() prototype */

int debug_level=0;

void catch_sigusr1(int sig_num)
{
    signal(SIGUSR1, catch_sigusr1);
    printf("\nIncrementing Debug Level by one\n");
    debug_level=debug_level+1;
    if (debug_level > 3) debug_level=3;
}

void catch_sigusr2(int sig_num)
{
    signal(SIGUSR2, catch_sigusr2);
    printf("\nDecrementing Debug Level by one\n");
    fflush(stdout);
    debug_level=debug_level-1;
    if (debug_level < 0) debug_level=0;
}

void main(int argc, char* argv[])
{
    /* set the signal handlers */
    signal(SIGUSR1, catch_sigusr1);
    signal(SIGUSR2, catch_sigusr2);

    /* enter an infinite loop of waiting for signals */
    for ( ;; )
    { 
	printf("Debug Level %i\n", debug_level);
        fflush(stdout);
	sleep(2);
    }
}
