/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_1_server.c $";

/*
 * Description:
 *  This pair of programs are meant to run on two servers - one as a client and 
 *  one as a server - with the IP addresses defined in the header file.. 
 */

/* Header Files */
#include "general_socket.h"

struct in_addr        localInterface;
struct sockaddr_in    groupSock;
int                   sd;
int                   datalen;
char                  databuf[1024];
int 		      message_id=0;

void
prepare_message(char * msg)
{
    /* Setup the message string */
    struct timespec curTime;        /* current time of day */
    struct tm       curTm;
    char            hostname[100];

    gethostname(hostname, sizeof(hostname) - 1);
    clock_gettime(CLOCK_REALTIME, &curTime);
    gmtime_r(&curTime.tv_sec, &curTm);

    /* Build the string */
    sprintf(msg, "Host:%s PID:%d MsgId:%d Time:%04d-%02d-%02dT%02d:%02d:%02d.%03ldZ\n",
        hostname, getpid(), message_id, curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday, 
		curTm.tm_hour, curTm.tm_min, curTm.tm_sec, curTime.tv_nsec / 1000000);
}

int main (int argc, char *argv[])
{
    // print a usage if there any arguments
    if (argc > 1)
    {
        printf("This demo server program is used to showcase the socket communication.\n");
        printf("The server was compiled for IP:%s\n", SERVER_IP);
        printf("The client was compiled for IP:%s\n", CLIENT_IP);
        printf("The multicast group was compiled for IP:%s\n", MULTICAST_GROUP_IP);
        printf("The multicast port was compiled with :%d\n\n", COMM_PORT);
        printf("No parameters required. Exiting.\n");
        exit(1);
    }

	/* ------------------------------------------------------------*/
	/*                                                             */
	/* Send Multicast Datagram code example.                       */
	/*                                                             */
	/* ------------------------------------------------------------*/

	/* Create a datagram socket on which to send.  */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) 
	{
		perror("opening datagram socket");
		exit(1);
	}

	/*
	* Initialize the group sockaddr structure with a
	* group address and port.
	*/
	memset((char *) &groupSock, 0, sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = inet_addr(MULTICAST_GROUP_IP);
	groupSock.sin_port = htons(COMM_PORT);

	/* Disable loopback so you do not receive your own datagrams.  */
	char loopch=0;

	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP,
	   (char *)&loopch, sizeof(loopch)) < 0) 
	{
		perror("setting IP_MULTICAST_LOOP:");
		close(sd);
		exit(1);
	}

	/*
	* Set local interface for outbound multicast datagrams.
	* The IP address specified must be associated with a local,
	* multicast-capable interface.
	*/
	localInterface.s_addr = inet_addr(SERVER_IP);
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface,
		sizeof(localInterface)) < 0)
	{
		printf("Tried to use %s - but unavailable\n", SERVER_IP);
		perror("setting local interface");
		exit(1);
	}

	/* Send a message to the multicast group specified by the groupSock sockaddr structure.  */
	while (1) 
	{
		for (int i = 0; i< 100; i++)
		{
			message_id = message_id + 1;
			prepare_message(databuf);
			printf("sending: %s\n", databuf);
			datalen = sizeof(databuf);

			if (sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)
			{
			    perror("sending datagram message");
			}
		}
		sleep(1);
	}
}
