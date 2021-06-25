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
 * The following is a multicast client/server that leverages threads. It is meant to
 * demonstrate :
 * 	1. pthreads - one thread will be for communications (send and receive)
 * 	2. multicasting between two or more linux servers (It will not work on a single 
 * 		server due to the multicast flag of listening to itself has been disabled.)
 * 	3. transferring different data types and a common message header
 * 	4. display the results to stdout.
 * It accepts two arguments:
 * 	multicast group
 * 	multicast port
 * This program is setup to use TWO or more servers to communicate.
 * 
 * Good site on sockets: https://www.tldp.org/HOWTO/Multicast-HOWTO-6.html
 */
#include <arpa/inet.h>
#include <strings.h>
#include <pthread.h>
#include <errno.h>
#include "general_socket.h"

/* Define structures */
union Payload_Type {
	short s;
	int i;
	float f;
	char str[PACKET_SIZE];
};

typedef struct msm_message
{
	int	    packet_id;
	char    hostname[20];
	struct  timespec packet_time;
	int	    payload_opcode;
	int	    payload_size;
	union Payload_Type payload;
} MSM_Message;

/* Global Variables */
unsigned short mc_port;      /* multicast port */
const char* mc_addr_str;     /* multicast IP address */

/* Description - seed the random number generator with the time */
void
init_random()
{
	time_t   t;

	/* Intializes random number generator */
	srand((unsigned) time(&t));
}

/* 
 * Description: 
 * The comm thread creates a message and then broadcasts it on the defined multicast group 
 */
void *
comm_thread()
{
	MSM_Message        msg;
	struct ip_mreq     mreq;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	socklen_t          addrlen;
	int                cnt;
    float              max_float = 100.0;

	/* set up socket */
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) 
	{
		perror("socket(): Socket Error in the client thread. Exiting.");
		exit(1);
	}
	bzero((char *)&s_addr, sizeof(s_addr));
	bzero((char *)&c_addr, sizeof(c_addr));
	bzero((char *)&msg, sizeof(msg));

    // Setup the client socket
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	c_addr.sin_port = htons(mc_port);

    // Setup the server socket
	s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(mc_addr_str);
	s_addr.sin_port = htons(mc_port);
	addrlen = sizeof(s_addr);


    /* Enable SO_REUSEADDR to allow multiple instances of this
       application to receive copies of the multicast datagrams.
    */
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
        sizeof(reuse)) < 0)
    {
        perror("setsockopt(): Setting SO_REUSEADDR error");
        close(sock);
        exit(1);
    }

    /* Set the timeout to 0.1 s when receiving a message */
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    /* IP_MULTICASE_LOOP: set loop to 1 to enable loopback or 0 to disable it */
    char loopch=0;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)
    {
        perror("setsockopt(): setting IP_MULTICAST_LOOP");
        close(sock);
        exit(1);
    }

    /* IP_MULTICAST_TTL: Set above 1 to go beyond local network. */
    char ttl=3;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) < 0)
    {
        perror("setsockopt(): setting IP_MULTICAST_TTL");
        close(sock);
        exit(1);
    }

    /* IP_MULTICAST_IF: Outgoing interface - To revert to the original behavior and
       let the kernel choose the outgoing interface based on the system administrator's
       configuration, it is enough to call setsockopt() with this same option and
       INADDR_ANY in the interface field.

        localInterface.s_addr = inet_addr(CLIENT_IP);
        if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface,
            sizeof(localInterface)) < 0)
        {
            perror("setsockopt(): setting local interface");
            close(sock);
            exit(1);
        }
    */

	/* receive */
	if (bind(sock, (struct sockaddr *) &c_addr, sizeof(c_addr)) < 0) 
	{        
		perror("bind(): Socket bind error in the client thread. Exiting.");
		exit(1);
	}    
	/* 
		struct ip_mreq
		{
            struct in_addr imr_multiaddr;    IP multicast address of group 
            struct in_addr imr_interface;    local IP address of interface
		};
		The first member, imr_multiaddr, holds the group address you want to join. 
		Remember that memberships are also associated with interfaces, not just groups. 
		This is the reason you have to provide a value for the second member: imr_interface. 
		This way, if you are in a multihomed host, you can join the same group in several 
		interfaces. You can always fill this last member with the wildcard address 
		(INADDR_ANY) and then the kernel will deal with the task of choosing the interface.
	*/
	mreq.imr_multiaddr.s_addr = inet_addr(mc_addr_str);         
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) 
	{
		perror("setsockopt(): Setting IP_ADD_MEMBERSHIP error - Client thread - exiting.");
		exit(1);
	}         
	while (1) 
	{
        /* Manage the message header info
           1. Increment the message packet id
           2. Get the hostname (This can be cached in a variable as a long term solution)
           3. Get the time
        */
        msg.packet_id = msg.packet_id + 1;
        gethostname(msg.hostname, sizeof(msg.hostname));
        clock_gettime(CLOCK_REALTIME, &msg.packet_time);

        msg.payload_opcode = rand() %5;
        printf(">>> Sending from host:%s G:%s M:%s: Id:%05d Opcode=%02d ", 
            msg.hostname, inet_ntoa(s_addr.sin_addr), CLIENT_IP, msg.packet_id, 
            msg.payload_opcode);

        struct tm curTm;
        switch (msg.payload_opcode)
        {
            case 0:
                // Use Zulu (UTC)
                gmtime_r(&(msg.packet_time.tv_sec), &curTm);
                sprintf(msg.payload.str,
                    "Host:%s Time is: %04d-%02d-%02dT%02d:%02d:%02d.%03ldZ",
                    msg.hostname, curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
                    curTm.tm_hour, curTm.tm_min, curTm.tm_sec,
                    msg.packet_time.tv_nsec / 1000000);
                msg.payload_size = strlen(msg.payload.str);
                printf("Size=%03d Type:string Message=\"%s\"\n",
                    msg.payload_size, msg.payload.str);
                break;

            case 1:
                sprintf(msg.payload.str, "Host:%s Test String", msg.hostname);
                msg.payload_size = strlen(msg.payload.str);
                printf("Size=%03d Type=char Message=\"%s\"\n",
                    msg.payload_size, msg.payload.str);
                break;

            case 2:
                msg.payload.i = rand()%10000;
                msg.payload_size = sizeof(msg.payload.i);
                printf("Size=%03d Type=integer Message=\"%4d\"\n",
                    msg.payload_size, msg.payload.i);
                break;

            case 3:
                msg.payload.f = ((float)rand()/(float)(RAND_MAX)) * max_float;
                msg.payload_size = sizeof(msg.payload.f);
                printf("Size=%03d Type=float Message=\"%04.3f\"\n",
                    msg.payload_size, msg.payload.f);
                break;

            default:
            case 4:
                msg.payload.s = rand()%1000;
                msg.payload_size = sizeof(msg.payload.s);
                printf("Size=%03d Type=short Message=\"%04u\"\n",
                    msg.payload_size, msg.payload.s);
                break;
        }

        cnt = sendto(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *) &s_addr, addrlen);
        if (cnt < 0)
        {
            perror("sendto");
            exit(1);
        }

        while((cnt = recvfrom(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *) &c_addr, 
			&addrlen)) > 0)
        {
            /* Print a formatted message on what we received - including the message header */
            printf("<<< Received from host:%s G:%s M:%s: Id:%05d Opcode=%02d Size=%03d ", 
                msg.hostname, inet_ntoa(mreq.imr_multiaddr), inet_ntoa(c_addr.sin_addr), 
                msg.packet_id, msg.payload_opcode, msg.payload_size);
            switch (msg.payload_opcode)
            {
                case 0:
                    printf("Type=time Message=\"%s\"\n", msg.payload.str);
                    break;

                case 1:
                    printf("Type=string Message=\"%s\"\n", msg.payload.str);
                    break;

                case 2:
                    printf("Type:integer Message=\"%03d\"\n", msg.payload.i);
                    break;

                case 3:
                    printf("Type=float Message=\"%04.3f\"\n", msg.payload.f);
                    break;

                default:
                case 4:
                    printf("Type=short Message=\"%04u\"\n", msg.payload.s);
                    break;
            }
        }
        sleep(1);
    }
}

int
main(int argc, const char* argv[])
{
	pthread_t     c_thread;

	printf("\n");
	printf("The demo program is a multicast client/server that leverages threads. It is \n");
	printf("meant to demonstrate :\n");
	printf("  1. pthreads - one thread will be server (sends multicast), and one is a client\n");
	printf("  2. multicasting between two or more linux servers (It will not work on a single\n");
	printf("     server due to the multicast flag of listening to itself has been disabled.)\n");
	printf("  3. transferring different data types and a common message header\n");
	printf("  4. display the results to stdout.\n");
	printf("It accepts two arguments:\n");
	printf("     multicast group\n");
	printf("     multicast port\n");
	printf("This program is setup to use TWO or more servers to communicate.\n");
	printf("\n");

	/* validate number of arguments */
	if (argc == 1)
	{
		mc_addr_str = "239.0.0.1";
		mc_port = 5555;
		fprintf(stderr, 
			"\nNo parameters used: Using default settings of '%s 239.0.0.1 5555'\n\n", 
			argv[0]);
	}
	else if (argc == 3)
	{
		mc_addr_str = argv[1];      /* arg 1: multicast ip address */
		mc_port = atoi(argv[2]);    /* arg 2: multicast port number */

		/* validate the port range */
		if ((mc_port < MIN_PORT) || (mc_port > MAX_PORT)) 
		{
			fprintf(stderr, "\nUsage: %s <Multicast IP> <Multicast Port>\n", argv[0]);
			fprintf(stderr, "  Invalid port number argument %d.\n", mc_port);
			fprintf(stderr, "  Valid range is between %d and %d.\n", MIN_PORT, MAX_PORT);
			fprintf(stderr, "Exiting.\n\n");
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "\nUsage: %s <Multicast IP> <Multicast Port>\n", argv[0]);
		fprintf(stderr, "  Valid port range is between %d and %d.\n", MIN_PORT, MAX_PORT);
		fprintf(stderr, "  Example: %s 239.0.0.1 5555\n", argv[0]);
		fprintf(stderr, "Exiting.\n\n");
		exit(1);
	}

	/* Random numbers are used in the program, so we need to seed this */
	init_random();

	/* create a thread which executes the server function */
	if (pthread_create(&c_thread, NULL, comm_thread, NULL))
	{
		fprintf(stderr, "Main Thread - Error creating comm thread\n");
		exit(1);
	}

	/* Join the threads to main process before exiting */
	pthread_join(c_thread, NULL);

	/* return to remove the warning message from the compiler. */
	return 1;
}
