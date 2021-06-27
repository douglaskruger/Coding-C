# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	tty_test 

tty_test: tty_test.o
	gcc tty_test.o -o tty_test

tty_test.o: tty_test.c
	gcc -c tty_test.c -o tty_test.o

clean:
	rm -f tty_test.o tty_test 
