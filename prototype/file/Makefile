# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================

all:	  read_line read_file

read_line: read_line.o
	gcc read_line.o -o read_line

read_file: read_file.o
	gcc read_file.o -o read_file

read_line.o: read_line.c
	gcc -c read_line.c -o read_line.o

read_file.o: read_file.c
	gcc -c read_file.c -o read_file.o

clean:
	rm -f read_line.o read_line read_file.o read_file
