/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_2_server.c $";

/*
 * Description:
 *   This prototype was built from information on the internet including sample 
 *   code. This was done to demonstrate an idea or technology.
 * 
 * Send numbers to the client in sequence: 0,1,2,3,...
 * Receive data from the client and verify that numbers are received in the 
 * expected sequence 0,4,8,12...
 *
 *    |------|                       |------|
 *    |      | === 0,4,8,12,... == > |      |
 *    |client|                       |server|
 *    |      | < == 0,1,2,3,... ==== |      |
 *    |------|                       |------|
 *
 * Sends data at a higher rate than the client (similar to most real 
 * client-server scenarios). Handles one client connection at a time. If that 
 * connection is disconnected, server will go back to listening for new connections
 */
#include <errno.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <sys/time.h>

#include "socket_2_lib.h"
#include "socket_2_stats.h"
#include "general_socket.h"

int 
main (int argc, char* argv[]) 
{
	struct timeval tv;
	fd_set readfds;
	
	// use listen port from cmd line args if supplied, otherwise use default value
	const char* listenPort = (argc > 1) ? argv[1] : COMM_PORT_S;

	conn_t* listenconn = listen_tcp(listenPort);
	if (!listenconn)
		return -1;

	printf("\nWaiting for connection on %s...\n", listenPort);
	while (1) 
	{
		// Accept a client socket
		conn_t* clientconn = accept_tcp(listenconn);
		if (!clientconn)
			continue;

		// connection stats - track how many bytes are sent/received and rates
		connxnstats_t* stats = stats_initialize(DEFAULT_STATS_INTERVAL);

		//"data" to send, and to receive and verify
		unsigned char recvCounter=0;
		unsigned char sendCounter=0;
		unsigned char recvBuf[2000];
		unsigned char sendBuf[2000];
		sendBuf[0] = 0;

		while (1) 
		{
			tv.tv_sec = 0;
			tv.tv_usec = 10000; //10ms
			FD_ZERO(&readfds);
			FD_SET(clientconn->sockfd, &readfds);

			//populate buffer to send
			for (int i=0; i<(int)sizeof(sendBuf); i++) 
			{
				sendBuf[i] = sendCounter++;
			}
			
			// check configured sockets
			if (select(clientconn->sockfd + 1, &readfds, NULL, NULL, &tv) == -1) 
			{
				perror("select failed\n");
				disconnect_tcp(clientconn);
				break;
			}

			// recv data if available
			if (FD_ISSET(clientconn->sockfd, &readfds)) 
			{
				int retVal = recvData(clientconn, (char*)recvBuf, (int)sizeof(recvBuf));
				if (retVal <= 0)
					break;
				stats_reportBytesRecd(stats, retVal); //report bytes received for stats
				
				//ensure integrity of data received
				for (int i=0; i<retVal; i++) 
				{
					assert(recvBuf[i] == recvCounter);
					recvCounter += 4;
				}
			}

			// send data
			int retVal = sendData(clientconn, (char*)sendBuf, (int)sizeof(sendBuf));
			if (retVal <= 0)
				break;
			stats_reportBytesSent(stats, retVal); //report bytes sent for stats
		}
		//print final stats before exiting and reset stats for next connection
		stats_finalize(stats);

		printf("\nWaiting for connection on %s...\n", listenPort);
	}
	
	disconnect_tcp(listenconn);
	return 1;
}
