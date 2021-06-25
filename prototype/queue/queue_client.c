/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: queue_client.c $";

/*
 * Description:
 * Prototype for a Linux queue client
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include "common.h"

int main(int argc, char **argv)
{
	mqd_t mq;
	char buffer[MAX_SIZE];

	/* open the mail queue */
	mq = mq_open(QUEUE_NAME, O_WRONLY);
	CHECK((mqd_t)-1 != mq);

	printf("Max Msg Size=%d\n", MAX_SIZE);
	printf("Send to server (enter \"exit\" to stop it):\n");

	int c=0;
	do 
	{
		sprintf(buffer, "My message is a wonderful message and I really like it!! Counter=%d\n", c);

		/* send the message */
		CHECK(0 <= mq_send(mq, buffer, MAX_SIZE, 0));
		c=c+1;
	} while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

	/* cleanup */
	CHECK((mqd_t)-1 != mq_close(mq));

	return 0;
}
