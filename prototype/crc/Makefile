# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================

# Requires the 'zlib' to be installed

all:	  simple_crc32 

simple_crc32: simple_crc32.o
	gcc -lz simple_crc32.o -o simple_crc32

simple_crc32.o: simple_crc32.c
	gcc -c simple_crc32.c -o simple_crc32.o

clean:
	rm -f simple_crc32.o simple_crc32 
