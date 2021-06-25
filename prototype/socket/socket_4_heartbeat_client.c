/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_4_heartbeat_client.c $";

/*
 * Description:
 * This prototype was based on code from the internet but updated.
 *
 * Demonstrates how to keep track of the server using a "heartbeat".  If the heartbeat is 
 * lost, the connection can be reestablished and the session resumed.
 */
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <resolv.h>
#include <signal.h>
#include <netinet/tcp.h>
#include "general_socket.h"

#define DELAY	5 

int serverfd, got_reply=1;

void 
sig_handler(int signum)
{
	if (signum == SIGURG)
	{   
		char c;
		recv(serverfd, &c, sizeof(c), MSG_OOB);
		got_reply = ( c == 'Y' );			  
		fprintf(stderr,"[got it]");
	} 
	else if (signum == SIGALRM)
	{
		if (got_reply)
		{
			send(serverfd, "?", 1, MSG_OOB);	 
			alarm(DELAY);				
			got_reply = 0;
		}
		else
			fprintf(stderr, "Lost connection to server!");
	}
}

int 
main(int count, char *strings[])
{	
	struct sockaddr_in addr;
	struct sigaction act;
	int bytes;
	char line[100];

	if (count != 3)
	{
		printf("usage: %s <addr> <port>\n", strings[0]);
		exit(0);
	}
	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGURG, &act, 0);
	sigaction(SIGALRM, &act, 0);

	serverfd = socket(PF_INET, SOCK_STREAM, 0);
	if ( fcntl(serverfd, F_SETOWN, getpid()) != 0 )
		perror("Can't claim SIGURG and SIGIO");
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(strings[2]));
	inet_aton(strings[1], &addr.sin_addr);

	if ( connect(serverfd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{
		alarm(DELAY);
		do
		{
			printf("\nPlease enter file name to receive:\n");
        		scanf("%s", line);
			printf("send [%s]\n", line);
			send(serverfd, line, strlen(line), 0);
			bytes = recv(serverfd, line, sizeof(line), 0);
		}
		while ( bytes > 0 );
	}
	else
		perror("connect failed");
	close(serverfd);
	return 0;
}

