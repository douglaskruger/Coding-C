/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: multicast_basic.c $";

/*
 * Description:
 *   The following program sends or receives multicast packets. If invoked
 *   with one argument, it sends a packet containing the current time to an
 *   arbitrarily chosen multicast group and UDP port. If invoked with no
 *   arguments, it receives and prints these packets. Start it as a sender on
 *   just one host and as a receiver on all the other hosts.
 *   
 *   With the current multicast settings, both the server and the client mode 
 *   can be run on the same server or multiple servers.
 *   
 *   Good site on sockets: https://www.tldp.org/HOWTO/Multicast-HOWTO-6.html
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include "general_socket.h"

int
main(int argc, const char* argv[])
{
	struct sockaddr_in addr;
	socklen_t addrlen;
    int sock, cnt;
	struct ip_mreq mreq;
	char message[50];

	printf("\n");
	printf("****************************************************************************\n");
	printf("This demonstration multicast program can run as a client or server based on \n");
	printf("the command line parameters. If there are NO command line parameters, then \n");
	printf("it will act as a client. If there are any command line parameters set (does \n");
	printf("not matter what the arguments are), then the program will act as the server.\n");
	printf("This program is meant to demonstrate multicasting across a single server or\n");
	printf("across two or more servers.\n");
	printf("In server mode, a multicast message will be sent out every 5 seconds.\n");
	printf("****************************************************************************\n");
	printf(" Sample Server Output\n");
	printf("  broadcasting msg: 'time is Sun Aug 25 14:18:42 2019'\n");
	printf(" Sample Client Output\n");
	printf("  Received from 192.168.1.111: msg: 'time is Sun Aug 25 14:19:02 2019'\n");
	printf("****************************************************************************\n");
	printf("\n");
 
	/* set up socket */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) 
	{
		perror("Error: socket creation.");
		exit(1);
	}
	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(COMM_PORT);
	addrlen = sizeof(addr);

	if (argc > 1) 
	{
		/* Multicast Server */
		printf("\nmulticast_basic -server mode G:%s P:%d\n", MULTICAST_GROUP_IP, COMM_PORT);
		addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP_IP);
		while (1) 
		{
			time_t t = time(0);
			sprintf(message, "time is %-24.24s", ctime(&t));
			printf("broadcasting msg: '%s'\n", message);
			cnt = sendto(sock, message, sizeof(message), 0,
				(struct sockaddr *) &addr, addrlen);
			if (cnt < 0) 
			{
				perror("Error: Server - sendto");
				exit(1);
			}
			sleep(5);
		}
	} 
	else 
	{
		/* Multicast Client */
		printf("\nmulticast_basic -client mode G:%s P:%d\n", MULTICAST_GROUP_IP, COMM_PORT);
		if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) 
		{        
			perror("Error: Client - bind");
			exit(1);
		}    
		mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP_IP);         
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
		if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) 
		{
			perror("setsockopt mreq");
			exit(1);
		}         
		while (1) 
		{
			cnt = recvfrom(sock, message, sizeof(message), 0, 
				(struct sockaddr *) &addr, &addrlen);
			if (cnt < 0) 
			{
				perror("Error: Client - recvfrom");
				exit(1);
			} 
			else if (cnt == 0) 
			{
				break;
			}
			printf("Received from %s: msg: '%s'\n", 
				inet_ntoa(addr.sin_addr), message);
		}
	}
}
