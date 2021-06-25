/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: socket_3_file_transfer_client.c$";

/*
 * Description:
 * 
 * client code for UDP socket programming
 */
#include "general_socket.h"

#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0

// funtion to clear buffer
void clearBuf(char* b)
{
	int i;
	for (i = 0; i < NET_BUF_SIZE; i++)
	{
		b[i] = '\0';
	}
}

// function for decryption
char Cipher(char ch)
{
	return ch ^ cipherKey;
}

// function to receive file
int recvFile(char* buf, int s)
{
	int i;
	char ch;
	for (i = 0; i < s; i++) 
	{
		ch = buf[i];
		ch = Cipher(ch);
		if (ch == EOF)
			return 1;
		else
			printf("%c", ch);
	}
	return 0;
}

// driver code
int 
main()
{
	int sockfd;
	struct sockaddr_in addr_con;
	socklen_t addrlen = sizeof(addr_con);

	addr_con.sin_family = AF_INET;
	addr_con.sin_port = htons(COMM_PORT);
	addr_con.sin_addr.s_addr = inet_addr(CLIENT_IP);
	char net_buf[NET_BUF_SIZE];

	// socket()
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

	if (sockfd < 0)
		printf("\nfile descriptor not received!!\n");
	else
		printf("\nfile descriptor %d received\n", sockfd);

	while (1) 
	{
		printf("\nPlease enter file name to receive:\n");
		scanf("%s", net_buf);
		sendto(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);

		printf("\n---------Data Received---------\n");
		while (1) 
		{
			// receive
			clearBuf(net_buf);
			int nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag, 
				(struct sockaddr*)&addr_con, &addrlen);
            printf("Bytes Received = %d\n", nBytes);

			// process
			if (recvFile(net_buf, NET_BUF_SIZE)) 
				break;
		}
		printf("\n-------------------------------\n");
	}
	return 0;
}
