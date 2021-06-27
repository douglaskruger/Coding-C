# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	nano_time time_formats timer_create_test-2 timer_create_test timer_example \
	timer_example2 timer_example3 uptime_example utc_time 

nano_time: nano_time.o
	gcc nano_time.o -o nano_time

nano_time.o: nano_time.c
	gcc -c nano_time.c -o nano_time.o

time_formats: time_formats.o
	gcc time_formats.o -o time_formats

time_formats.o: time_formats.c
	gcc -c time_formats.c -o time_formats.o

timer_create_test-2: timer_create_test-2.o
	gcc timer_create_test-2.o -o timer_create_test-2

timer_create_test-2.o: timer_create_test-2.c
	gcc -c timer_create_test-2.c -o timer_create_test-2.o

timer_create_test: timer_create_test.o
	gcc timer_create_test.o -o timer_create_test

timer_create_test.o: timer_create_test.c
	gcc -c timer_create_test.c -o timer_create_test.o

timer_example: timer_example.o
	gcc timer_example.o -o timer_example

timer_example.o: timer_example.c
	gcc -c timer_example.c -o timer_example.o

timer_example2: timer_example2.o
	gcc timer_example2.o -o timer_example2

timer_example2.o: timer_example2.c
	gcc -c timer_example2.c -o timer_example2.o

timer_example3: timer_example3.o
	gcc timer_example3.o -o timer_example3

timer_example3.o: timer_example3.c
	gcc -c timer_example3.c -o timer_example3.o

uptime_example: uptime_example.o
	gcc uptime_example.o -o uptime_example

uptime_example.o: uptime_example.c
	gcc -c uptime_example.c -o uptime_example.o

utc_time: utc_time.o
	gcc utc_time.o -o utc_time

utc_time.o: utc_time.c
	gcc -c utc_time.c -o utc_time.o

clean:
	rm -f nano_time.o nano_time time_formats.o time_formats \
		timer_create_test-2.o timer_create_test-2 timer_create_test.o timer_create_test timer_example.o timer_example \
		timer_example2.o timer_example2 timer_example3.o timer_example3 uptime_example.o uptime_example \
		utc_time.o utc_time 
