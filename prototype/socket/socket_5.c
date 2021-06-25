#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <net/if.h>
#include "general_socket.h"

void
get_adapter_ip(char * name)
{
    int fd;
    struct ifreq ifr;
    
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    // I want to get an IPv4 IP address 
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, name, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);

    // Close the socket
    close(fd);

    /* display result */
    printf("Adapter: %s has IP: %s\n", name, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}

int
main()
{
    get_adapter_ip("eth0");
    get_adapter_ip("eth1");
}
