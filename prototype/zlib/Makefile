# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	gzip_example zlib_example1 zlib_minigzip 

gzip_example: gzip_example.o
	gcc -lz gzip_example.o -o gzip_example

gzip_example.o: gzip_example.c
	gcc -c gzip_example.c -o gzip_example.o

zlib_example1: zlib_example1.o
	gcc -lz zlib_example1.o -o zlib_example1

zlib_example1.o: zlib_example1.c
	gcc -c zlib_example1.c -o zlib_example1.o

zlib_minigzip: zlib_minigzip.o
	gcc -lz zlib_minigzip.o -o zlib_minigzip

zlib_minigzip.o: zlib_minigzip.c
	gcc -c zlib_minigzip.c -o zlib_minigzip.o

clean:
	rm -f gzip_example.o gzip_example zlib_example1.o zlib_example1 \
		zlib_minigzip.o zlib_minigzip 
