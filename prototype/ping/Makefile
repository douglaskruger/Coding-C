# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	my_ping 

my_ping: my_ping.o
	gcc my_ping.o -o my_ping

my_ping.o: my_ping.c
	gcc -c my_ping.c -o my_ping.o

clean:
	rm -f my_ping.o my_ping 
