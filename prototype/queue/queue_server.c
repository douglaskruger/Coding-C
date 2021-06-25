/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: queue_server.c $";

/*
 * Description:
 * Prototype server code for Linux queues.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include "common.h"

int 
main(int argc, char **argv)
{
	mqd_t mq;
	struct mq_attr attr;
	char buffer[MAX_SIZE + 1];
	int must_stop = 0;

	/* initialize the queue attributes */
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;

	/* create the message queue */
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
	CHECK((mqd_t)-1 != mq);

	do 
	{
		ssize_t bytes_read;

		/* receive the message */
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
		CHECK(bytes_read >= 0);

		buffer[bytes_read] = '\0';
		if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
		{
			must_stop = 1;
		}
		else
		{
			printf("Received: %s\n", buffer);
		}
	} while (!must_stop);

	/* cleanup */
	CHECK((mqd_t)-1 != mq_close(mq));
	CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

	return 0;
}
