/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: get_rusage.c$";

/*==============================================================================
  Description:
  Demonstration of getting Linux process details
==============================================================================*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <stdio.h> 
#include <sys/time.h>   
#include <sys/resource.h> 
#include <unistd.h>

//*****************************************************************************
// measure user and system time using the "getrusage" call. 
//*****************************************************************************
//struct rusage {
//   struct timeval ru_utime; /* user CPU time used */
//   struct timeval ru_stime; /* system CPU time used */
//   long   ru_maxrss;        /* maximum resident set size */
//   long   ru_ixrss;         /* integral shared memory size */
//   long   ru_idrss;         /* integral unshared data size */
//   long   ru_isrss;         /* integral unshared stack size */
//   long   ru_minflt;        /* page reclaims (soft page faults) */
//   long   ru_majflt;        /* page faults (hard page faults) */
//   long   ru_nswap;         /* swaps */
//   long   ru_inblock;       /* block input operations */
//   long   ru_oublock;       /* block output operations */
//   long   ru_msgsnd;        /* IPC messages sent */
//   long   ru_msgrcv;        /* IPC messages received */
//   long   ru_nsignals;      /* signals received */
//   long   ru_nvcsw;         /* voluntary context switches */
//   long   ru_nivcsw;        /* involuntary context switches */
//};

//struct timeval
//  {
//    long int tv_sec;       /* Seconds.  */
//    long int tv_usec;      /* Microseconds.  */
//  };

// Returns the size of physical memory (RAM) in bytes.
size_t getMemorySize( )
{
    return (size_t)sysconf( _SC_PHYS_PAGES ) * (size_t)sysconf( _SC_PAGESIZE );
}

int 
main(int argc, char** argv)
{ 
    struct rusage r_usage;

    // chew up some CPU time at first
    int j = 0;
    for (int i=0; i<100000000; i++) 
    { 
        j+=i*i; 
    }     
    char  buffer[50000] = "This program returns process statistics";
    printf("%s\n", buffer);
    printf("System Memory=%lu\n",getMemorySize());

    getrusage(RUSAGE_SELF,&r_usage);

    // Print the maximum resident set size used (in kilobytes).
    printf("Mesg Send: %ld \n",r_usage.ru_msgsnd);
    printf("Context: %ld \n",r_usage.ru_nvcsw);
    printf("Involuntary Context: %ld \n",r_usage.ru_nivcsw);
    printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);

    printf("User seconds without microseconds: %ld\n", r_usage.ru_utime.tv_sec); 
    printf("User microseconds: %ld\n", r_usage.ru_utime.tv_usec); 
    printf("Total user seconds: %e\n", (double) r_usage.ru_utime.tv_sec 
        + (double) r_usage.ru_utime.tv_usec / (double) 1000000); 
} 
