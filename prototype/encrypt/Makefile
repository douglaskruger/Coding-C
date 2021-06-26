# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================

# Requires the 'zlib' to be installed

all:	  encrypt1 

encrypt1: encrypt1.o
	gcc encrypt1.o -o encrypt1

encrypt1.o: encrypt1.c
	gcc -c encrypt1.c -o encrypt1.o

clean:
	rm -f encrypt1.o encrypt1 
