/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#ifndef SOCKET_1_H
#define SOCKET_1_H

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*==============================================================================
                              Defines
==============================================================================*/
// Setup the appropriate port and IP addresses for your two server test system
#define IP_PROTOCOL 0
#define CLIENT_IP "192.168.1.60"
#define SERVER_IP "192.168.1.61"
#define MULTICAST_GROUP_IP "225.1.1.1"
#define COMM_PORT 5555
#define COMM_PORT_S "5555"
#define MIN_PORT 1024   /* minimum port allowed */
#define MAX_PORT 65535  /* maximum port allowed */
#define PACKET_SIZE 1200

#endif
