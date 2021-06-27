# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	signal-handling-1 signal-handling-2 signal-handling-3 

signal-handling-1: signal-handling-1.o
	gcc signal-handling-1.o -o signal-handling-1

signal-handling-1.o: signal-handling-1.c
	gcc -c signal-handling-1.c -o signal-handling-1.o

signal-handling-2: signal-handling-2.o
	gcc signal-handling-2.o -o signal-handling-2

signal-handling-2.o: signal-handling-2.c
	gcc -c signal-handling-2.c -o signal-handling-2.o

signal-handling-3: signal-handling-3.o
	gcc signal-handling-3.o -o signal-handling-3

signal-handling-3.o: signal-handling-3.c
	gcc -c signal-handling-3.c -o signal-handling-3.o

clean:
	rm -f signal-handling-1.o signal-handling-1 signal-handling-2.o signal-handling-2 \
		signal-handling-3.o signal-handling-3 
