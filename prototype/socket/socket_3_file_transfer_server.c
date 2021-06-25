/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_3_file_transfer_server.c$";

/*
 * Description:
 * 
 * server code for UDP socket programming
 */
#include "general_socket.h"

#define IP_PROTOCOL 0
#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0
#define nofile "File Not Found!"

// funtion to clear buffer
void 
clearBuf(char* b)
{
	int i;
	for (i = 0; i < NET_BUF_SIZE; i++)
	{
		b[i] = '\0';
	}
}

// function to encrypt
char 
cipher(char ch)
{
	return ch ^ cipherKey;
}

// funtion sending file
int 
sendFile(FILE* fp, char* buf, int s)
{
	int i, len;

	if (fp == NULL) 
	{
		strcpy(buf, nofile);
		len = strlen(nofile);
		buf[len] = EOF;
		for (i = 0; i <= len; i++)
		buf[i] = cipher(buf[i]);
		return 1;
	}

	char ch, ch2;
	for (i = 0; i < s; i++) 
	{
		ch = fgetc(fp);
		ch2 = cipher(ch);
		buf[i] = ch2;
		if (ch == EOF)
		return 1;
	}
	return 0;
}

// driver code
int 
main()
{
	FILE* fp;
	int sockfd, nBytes;
	struct sockaddr_in addr_con;
	socklen_t addrlen = sizeof(addr_con);

	addr_con.sin_family = AF_INET;
	addr_con.sin_port = htons(COMM_PORT);
	addr_con.sin_addr.s_addr = INADDR_ANY;
	char net_buf[NET_BUF_SIZE];

	// socket()
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

	if (sockfd < 0)
		printf("\nfile descriptor not received!!\n");
	else
		printf("\nfile descriptor %d received\n", sockfd);

	// bind()
	if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0)
		printf("\nSuccessfully binded!\n");
	else
		printf("\nBinding Failed!\n");

	while (1) 
	{
		printf("\nWaiting for file name...\n");

		// receive file name
		clearBuf(net_buf);

		nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag,
			(struct sockaddr*)&addr_con, &addrlen);
        printf("Bytes Received = %d\n", nBytes);


		fp = fopen(net_buf, "r");
		printf("\nFile Name Received: %s\n", net_buf);
		if (fp == NULL)
			printf("\nFile open failed!\n");
		else
			printf("\nFile Successfully opened!\n");

		while (1) 
		{
			// process
			if (sendFile(fp, net_buf, NET_BUF_SIZE)) 
			{
				sendto(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag,
					(struct sockaddr*)&addr_con, addrlen);
				break;
			}

			// send
			sendto(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag,
				(struct sockaddr*)&addr_con, addrlen);
			clearBuf(net_buf);
		}
		if (fp != NULL)
			fclose(fp);
	}
	return 0;
}
