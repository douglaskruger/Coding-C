/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_2_client.c$";

/*
 * Description:
 *   This is a dummy TCP socket client application.
 *   Send numbers to the server in the sequence: 0,4,8,12,...
 *   Receive data from the server and verify that numbers are received in the 
 *   expected sequence 0,1,2,3,...
 *
 *    |------|                       |------|
 *    |      | === 0,4,8,12,... == > |      |
 *    |client|                       |server|
 *    |      | < == 0,1,2,3,... ==== |      |
 *    |------|                       |------|
 *
 *  The client sends data at a lower rate than the server does (similar to most 
 *  real client-server scenarios).
 */

/* Headers */
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <sys/time.h>
#include "general_socket.h"
#include "socket_2_lib.h"
#include "socket_2_stats.h"

int 
main (int argc, char* argv[]) 
{
	fd_set readfds;
	struct timeval tv;

	// use server IP:port from cmd line args if supplied, otherwise use default values
	const char* serverIP = (argc > 1) ? argv[1] : SERVER_IP;
	const char* serverPort = (argc > 2) ? argv[2] : COMM_PORT_S;

	printf("Ensure that the corresponding server process is running first\n");
	printf("Connecting to server %s:%s...\n", serverIP, serverPort);

	conn_t* serverconn = connect_tcp(serverIP, serverPort);
	if (!serverconn)
		return -1;

	// connection stats
	connxnstats_t* stats = stats_initialize(DEFAULT_STATS_INTERVAL);

	//"data" to send, and to receive and verify
	unsigned char recvCounter=0; // counter to check received values are as expected and in order
	unsigned char recvBuf[2000];
	unsigned char sendBuf[1];
	sendBuf[0] = 0;

	while (1) {
		tv.tv_sec = 0;
		tv.tv_usec = 10000; // 10ms
		FD_ZERO(&readfds);
		FD_SET(serverconn->sockfd, &readfds);
		
		if (select(serverconn->sockfd + 1, &readfds, NULL, NULL, &tv) == -1) 
		{
			perror("select failed\n");
			disconnect_tcp(serverconn);
			break;
		}
		
		// recv data if available
		if (FD_ISSET(serverconn->sockfd, &readfds)) 
		{
			// recv data
			int retVal = recvData(serverconn, (char*)recvBuf, (int)sizeof(recvBuf));
			if (retVal <= 0)
				break;

			// report stats
			stats_reportBytesRecd(stats, retVal); //stats reporting

			// ensure integrity of data received
			for(int i=0; i<retVal; i++) 
			{
				assert(recvBuf[i] == recvCounter++);
			}
		}

		// send data
		if (sendBuf[0]%4 == 0) 
		{
			int retVal = sendData(serverconn, (char*)sendBuf, (int)sizeof(sendBuf));
			if (retVal <= 0)
				break;

			// report stats
			stats_reportBytesSent(stats, retVal); //stats reporting
		}
		sendBuf[0] = sendBuf[0] + 1;
	}

	// print final stats before exiting
	stats_finalize(stats);

	return 0;
}
