/* 

multicast.c

The following program sends or receives multicast packets. If invoked
with one argument, it sends a packet containing the current time to an
arbitrarily chosen multicast group and UDP port. If invoked with no
arguments, it receives and prints these packets. Start it as a sender on
just one host and as a receiver on all the other hosts

Good site: https://www.tldp.org/HOWTO/Multicast-HOWTO-6.html
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <pthread.h>
#include <string.h>

#define EXAMPLE_PORT 5555
#define EXAMPLE_GROUP "239.0.0.1"
#define LOCAL_IP_ADDRESS "192.168.1.111"
#define PACKET_SIZE 1200

union Payload_Type {
	short s;
	int i;
	float f;
	char str[PACKET_SIZE];
};

typedef struct msm_message
{
	int	packet_id;
	char    hostname[20];
	struct  timespec packet_time;
	int	payload_opcode;
	int	payload_size;
	union Payload_Type payload;
} MSM_Message;

void
init_random()
{
    time_t                t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));
}

void *
server_thread() 
{
   MSM_Message msg;
   struct tm       curTm;
   int addrlen;
   struct sockaddr_in addr;
   struct in_addr        localInterface;
   int cnt;

   /* set up socket */
   int sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     exit(1);
   }
   bzero((char *)&addr, sizeof(addr));
   bzero((char *)&msg, sizeof(msg));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(EXAMPLE_GROUP);
   addr.sin_port = htons(EXAMPLE_PORT);
   addrlen = sizeof(addr);

    /* IP_MULTICASE_LOOP: set loop to 1 to enable loopback or 0 to disable it */
    char loopch=0;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)
    {
        perror("setting IP_MULTICAST_LOOP");
        close(sock);
        exit(1);
    }

    /* IP_MULTICAST_TTL: Set above 1 to go beyond local network. */
    char ttl=3;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) < 0)
    {
        perror("setting IP_MULTICAST_TTL");
        close(sock);
        exit(1);
    }

    /* IP_MULTICAST_IF: Outgoing interface - To revert to the original behavior and let the 
       kernel choose the outgoing interface based on the system administrator's configuration, 
       it is enough to call setsockopt() with this same option and INADDR_ANY in the interface field.
    */
    localInterface.s_addr = inet_addr(LOCAL_IP_ADDRESS);
/*
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        perror("setting local interface");
        close(sock);
        exit(1);
    }
*/
      /* send */
      while (1) {
	 msg.packet_id = msg.packet_id + 1;
	 gethostname(msg.hostname, sizeof(msg.hostname));
         clock_gettime(CLOCK_REALTIME, &msg.packet_time);
	float max_float = 100.0;

        msg.payload_opcode = rand() %5;
        printf("Sending  from host:%s G:%s M:%s: Id:%05d Opcode=%02d ", msg.hostname, inet_ntoa(addr.sin_addr), 
		LOCAL_IP_ADDRESS, msg.packet_id, msg.payload_opcode, msg.payload_size);
	switch (msg.payload_opcode)
	{
		case 0:
        		localtime_r(&(msg.packet_time.tv_sec), &curTm);
        		sprintf(msg.payload.str, "Time is: %04d.%02d.%02d-%02d:%02d:%02d.%03ld",
               			curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
               			curTm.tm_hour, curTm.tm_min, curTm.tm_sec, msg.packet_time.tv_nsec / 1000000);
	 		msg.payload_size = strlen(msg.payload.str);
         		printf("Size=%03d Type:time    Message=\"%s\"\n", msg.payload_size, msg.payload.str);
			break;

		case 1:
			sprintf(msg.payload.str, "Test String");
	 		msg.payload_size = strlen(msg.payload.str);
         		printf("Size=%03d Type=char    Message=\"%s\"\n", msg.payload_size, msg.payload.str);
			break;

		case 2:
			msg.payload.i = rand()%10000;
	 		msg.payload_size = sizeof(msg.payload.i);
         		printf("Size=%03d Type=integer Message=\"%4d\"\n", msg.payload_size, msg.payload.i);
			break;

		case 3:
			msg.payload.f = ((float)rand()/(float)(RAND_MAX)) * max_float; 
	 		msg.payload_size = sizeof(msg.payload.f);
         		printf("Size=%03d Type=float   Message=\"%04.3f\"\n", msg.payload_size, msg.payload.f);
			break;

		default:
		case 4:
			msg.payload.s = rand()%1000;
	 		msg.payload_size = sizeof(msg.payload.s);
         		printf("Size=%03d Type=short   Message=\"%04u\"\n", msg.payload_size, msg.payload.s);
			break;
	 }
         cnt = sendto(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *) &addr, addrlen); 
	 if (cnt < 0)
	 {
            perror("sendto");
            exit(1);
         }
         sleep(2);
      }
}

void *
client_thread()
{
   MSM_Message msg;
   struct ip_mreq mreq;
   int addrlen;
   struct sockaddr_in addr;
   int cnt;

   /* set up socket */
   int sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     exit(1);
   }
   bzero((char *)&addr, sizeof(addr));
   bzero((char *)&msg, sizeof(msg));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(EXAMPLE_PORT);

   addrlen = sizeof(addr);

      /* receive */
      if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {        
         perror("bind");
	 exit(1);
      }    
      /* struct ip_mreq
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
      mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);         
      mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
      if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
	 perror("setsockopt mreq");
	 exit(1);
      }         
      while (1) {
 	 cnt = recvfrom(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *) &addr, &addrlen);
	 if (cnt < 0) {
	    perror("recvfrom");
	    exit(1);
	 } else if (cnt == 0) {
 	    break;
	 }
         printf("Received from host:%s G:%s M:%s: Id:%05d Opcode=%02d Size=%03d ", msg.hostname, 
		inet_ntoa(mreq.imr_multiaddr), LOCAL_IP_ADDRESS, msg.packet_id, msg.payload_opcode, 
		msg.payload_size);
        switch (msg.payload_opcode)
	{
                case 0:
         		printf("Type=string  Message=\"%s\"\n", msg.payload.str);
                        break;

                case 1:
         		printf("Type=string  Message=\"%s\"\n", msg.payload.str);
                        break;

                case 2:
         		printf("Type:integer Message=\"%03d\"\n", msg.payload.i);
                        break;

		case 3:
         		printf("Type=float   Message=\"%04.3f\"\n", msg.payload.f);
			break;

		default:
		case 4:
         		printf("Type=short   Message=\"%04u\"\n", msg.payload.s);
			break;
         }
    }
}

int
main(int argc, const char* argv[])
{
    pthread_t     c_thread;
    pthread_t     s_thread;

    init_random();

    /* create a thread which executes the server function */
    if(pthread_create(&s_thread, NULL, server_thread, NULL))
    {
        fprintf(stderr, "Error creating thread\n");
        exit(1);
    }

    /* create a thread which executes the server function */
    if(pthread_create(&c_thread, NULL, client_thread, NULL))
    {
        fprintf(stderr, "Error creating thread\n");
        exit(1);
    }

    pthread_join(s_thread, NULL);
    pthread_join(c_thread, NULL);

    return 1;
}
