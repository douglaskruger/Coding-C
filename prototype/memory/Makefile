# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	get_rusage set_limits 

get_rusage: get_rusage.o
	gcc get_rusage.o -o get_rusage

get_rusage.o: get_rusage.c
	gcc -c get_rusage.c -o get_rusage.o

set_limits: set_limits.o
	gcc set_limits.o -o set_limits

set_limits.o: set_limits.c
	gcc -c set_limits.c -o set_limits.o

clean:
	rm -f get_rusage.o get_rusage set_limits.o set_limits 
