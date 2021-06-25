/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_4_heartbeat_server.c $";

/*
 * Description:
 * Demonstrates how to keep track of the server using a "heartbeat". If the heartbeat is 
 * lost, the connection can be reestablished and the session resumed.
 */
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <resolv.h>
#include <signal.h>
#include "general_socket.h"

int client;
struct sigaction act;

void 
sig_handler(int signum)
{
	if (signum == SIGURG)
	{   
		char c;
		recv(client, &c, sizeof(c), MSG_OOB);
		if (c == '?')				   
			send(client, "Y", 1, MSG_OOB);	
	}
	else if (signum == SIGCHLD)
		wait(0);
}

void 
servlet(void)
{	
	int bytes;
	char buffer[1024];

	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGURG, &act, 0);	
	if (fcntl(client, F_SETOWN, getpid()) != 0)
		perror("Can't claim SIGIO and SIGURG");
	do
	{
		bytes = recv(client, buffer, sizeof(buffer), 0);
		if (bytes > 0)
			send(client, buffer, bytes, 0);
	} while (bytes > 0);
	close(client);
	exit(0);
}

int 
main(int count, char *strings[])
{	
	int sd;
	struct sockaddr_in addr;

	if (count != 2)
	{
		printf("usage: %s <port>\n", strings[0]);
		exit(0);
	}
	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	if (sigaction(SIGCHLD, &act, 0) != 0)
		perror("sigaction()");

	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(strings[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
		perror("bind()");

	listen(sd, 15);
	for (;;)
	{
		client = accept(sd, 0, 0);
		if (client > 0)
		{
			if (fork() == 0)
			{
				close(sd);
				servlet();
			}
			else
				close(client);
		}
		else
			perror("accept()");
	}
	close(sd);
	return 0;
}
