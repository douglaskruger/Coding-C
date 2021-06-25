/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#ifndef __STATS_H
#define __STATS_H

#define DEFAULT_STATS_INTERVAL  2 //in seconds

typedef struct {
	unsigned int bytesSent;
	unsigned int bytesRecd;
	unsigned long bytesSent_total;
	unsigned long bytesRecd_total;
	int updateInterval;
	pthread_t updateThread;
} connxnstats_t;

connxnstats_t* stats_initialize(int updateInterval);
void stats_reportBytesSent(connxnstats_t* stats, unsigned int bytesSent);
void stats_reportBytesRecd(connxnstats_t* stats, unsigned int bytesRecd);
void stats_finalize(connxnstats_t* stats);
void stats_refresh(connxnstats_t* stats);
void stats_readifyNum(int num, char* readableNumStr);

#endif
