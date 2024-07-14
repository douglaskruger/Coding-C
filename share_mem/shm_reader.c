#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IP_PROTOCOL 0

typedef struct TEM_IO
{
        char   Name[100];
        short  ObjectId;
        double Voltage;
        double Current;
        double Temperature;
        double StateOfCharge;
} tzTEM_IO;
  
int main() 
{ 
    struct in_addr        localInterface;
    struct sockaddr_in    addr_con;
    int 		  sockfd;
    time_t 		  t;
    struct ip_mreq        group;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    // socket()
    sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

    if (sockfd < 0)
    {
	perror("Error opening datagram socket");
	exit(1);
    }

  /* Initialize the group sockaddr structure with a
   * group address of 225.1.1.1 and port 5555.
   */
  memset((char *) &addr_con, 0, sizeof(addr_con));
  addr_con.sin_family = AF_INET;
  addr_con.sin_port = htons(5555);

  /* Disable loopback so you do not receive your own datagrams.  */
#ifdef SERVER
printf("Server\n");
  addr_con.sin_addr.s_addr = inet_addr("225.1.1.1");
  {
    char loopch=0;

    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char *)&loopch, sizeof(loopch)) < 0) {
      perror("setting IP_MULTICAST_LOOP:");
      close(sockfd);
      exit(1);
    }
  }
  localInterface.s_addr = inet_addr("192.168.1.104");
  if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface,
        sizeof(localInterface)) < 0)
  {
    perror("setting local interface");
    exit(1);
  }
#else
printf("Client\n");
  addr_con.sin_addr.s_addr = INADDR_ANY;

  /*
   * Enable SO_REUSEADDR to allow multiple instances of this
   * application to receive copies of the multicast datagrams.
   */
  {
    int reuse=1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&reuse, sizeof(reuse)) < 0) {
      perror("setting SO_REUSEADDR");
      close(sockfd);
      exit(1);
    }
  }
 if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con))) {
    perror("binding datagram socket");
    close(sockfd);
    exit(1);
  }
  /*
   * Join the multicast group 225.1.1.1 on the local 9.5.1.1
   * interface.  Note that this IP_ADD_MEMBERSHIP option must be
   * called for each local interface over which the multicast
   * datagrams are to be received.
   */
  group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
  group.imr_interface.s_addr = inet_addr("192.168.1.104");
  if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                 (char *)&group, sizeof(group)) < 0) {
    perror("adding multicast group");
    close(sockfd);
    exit(1);
  }
#endif

    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096000,0666|IPC_CREAT);
    if (shmid < 0)
    {
        printf("Could not get shared memory. Error=%d\n. Exiting.\n\n", errno);
        exit(1);
    }

    // shmat to attach to shared memory 
    tzTEM_IO *tem = (tzTEM_IO *) shmat(shmid,(void*)0,0);
  
    /* Populate the initial values of local memory */
    printf("*** Initialization\n");
    for (int i=0; i<10000; i++)
    {
        sprintf(tem[i].Name, "TEM I/O-%d", i);
        tem[i].Voltage = rand() % 20;
        tem[i].ObjectId = i +10000;
        tem[i].Current = rand() % 20;
        tem[i].Temperature = rand() % 20;
        tem[i].StateOfCharge = rand() % 20;

        printf("Object Index=%d\n",i);
        printf("  Name: %s\n", tem[i].Name);
        printf("  ObjectId: %d\n", tem[i].ObjectId);
        printf("  Voltage: %f\n", tem[i].Voltage);
        printf("  Current: %f\n", tem[i].Current);
        printf("  Temperature: %f\n", tem[i].Temperature);
        printf("  StateOfCharge: %f\n", tem[i].StateOfCharge);
    }
    printf("*** Running\n");

    while (1) 
    {
	int i;
#ifdef SERVER
        printf("Update a million records\n");
        for (int count=0;count<1000000;count++)
        {
            i = rand() %10000;
            sprintf(tem[i].Name, "TEM I/O-%d-%d", i, rand() %80);
            tem[i].Voltage = rand() % 20;
            tem[i].Current = rand() % 20;
            tem[i].Temperature = rand() % 20;
            tem[i].StateOfCharge = rand() % 20;
        }

        // send the first 1000 objects to the other via multicast
	printf("Multicast objects!\n");
	for (i=0;i<1000;i++)
	{
	   if (sendto(sockfd, (void *)&tem[i], sizeof(tzTEM_IO), 0,
              	  (struct sockaddr*)&addr_con, sizeof(addr_con)) < 0)
	   {
		perror("Error sending datagram");
	   }
	}
#else
	for (i=0;i<1000;i++)
        {
	    if (read(sockfd, (void *)&tem[i], sizeof(tzTEM_IO)) < 0) 
            {
            	perror("reading datagram message");
            	close(sockfd);
            	exit(1);
            }
        }
        for (int count=0;count<100;count++)
        {
           i = rand() %10000;
           printf("Object Index=%d\n",i);
           printf("  Name: %s\n", tem[i].Name);
           printf("  ObjectId: %d\n", tem[i].ObjectId);
           printf("  Voltage: %f\n", tem[i].Voltage);
           printf("  Current: %f\n", tem[i].Current);
           printf("  Temperature: %f\n", tem[i].Temperature);
           printf("  StateOfCharge: %f\n", tem[i].StateOfCharge);
	}
#endif
     	sleep(1);
    }
 
    //detach from shared memory  
    shmdt(tem); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 
