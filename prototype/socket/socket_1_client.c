/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_1_client.c $";

/*
 * Description:
 *   Socket demonstration   
 */

#include "general_socket.h"

struct sockaddr_in    localSock;
struct ip_mreq        group;
int                   sd;
int                   datalen;
char                  databuf[1024];

void
print_message(char * msg)
{
        /* Setup the message string */
        struct timespec curTime;        /* current time of day */
        struct tm       curTm;
        char            hostname[100];

        gethostname(hostname, sizeof(hostname) - 1);
        clock_gettime(CLOCK_REALTIME, &curTime);
        gmtime_r(&curTime.tv_sec, &curTm);

        /* Build the string */
        printf("Host:%s PID:%d Time:%04d-%02d-%02dT%02d:%02d:%02d.%03ldZ - Msg Received:\"%s\"\n",
                hostname, getpid(), curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
                curTm.tm_hour, curTm.tm_min, curTm.tm_sec, curTime.tv_nsec / 1000000, msg);
}

int 
main (int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("This demo client program is used to showcase the socket communication.\n");
        printf("The server was compiled for IP:%s\n", SERVER_IP);
        printf("The client was compiled for IP:%s\n", CLIENT_IP);
        printf("The multicast group was compiled for IP:%s\n", MULTICAST_GROUP_IP);
        printf("The multicast port was compiled with :%d\n\n", COMM_PORT);
        printf("No parameters required. Exiting.\n");
        exit(1);
    }

	/* ------------------------------------------------------------*/
	/*                                                             */
	/* Receive Multicast Datagram code example.                    */
	/*                                                             */
	/* ------------------------------------------------------------*/

	/*
	* Create a datagram socket on which to receive.
	*/
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) 
	{
		perror("opening datagram socket");
		exit(1);
	}

	/*
	* Enable SO_REUSEADDR to allow multiple instances of this
	* application to receive copies of the multicast datagrams.
	*/
	int reuse=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) 
	{
		perror("setting SO_REUSEADDR");
		close(sd);
		exit(1);
	}

	/*
	* Bind to the proper port number with the IP address
	* specified as INADDR_ANY.
	*/
	memset((char *) &localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(COMM_PORT);;
	localSock.sin_addr.s_addr  = INADDR_ANY;

	if (bind(sd, (struct sockaddr*)&localSock, sizeof(localSock))) 
	{
		perror("binding datagram socket");
		close(sd);
		exit(1);
	}

	/*
	* Join the multicast group MULTICAST_GROUP_IP on the local IP
	* interface.  Note that this IP_ADD_MEMBERSHIP option must be
	* called for each local interface over which the multicast
	* datagrams are to be received.
	*/
	group.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP_IP);

	/* Local workstation IP */
	group.imr_interface.s_addr = inet_addr(CLIENT_IP);
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		 (char *)&group, sizeof(group)) < 0) 
	{
        printf("Error in attaching the %s address for group %s\n", CLIENT_IP, MULTICAST_GROUP_IP);
		perror("adding multicast group");
		close(sd);
		exit(1);
	}

	/* Read from the socket.  */
	while (1) 
	{
		datalen = sizeof(databuf);
		if (read(sd, databuf, datalen) < 0) 
		{
			perror("reading datagram message");
			close(sd);
			exit(1);
		}
		print_message(databuf);
	}
}
