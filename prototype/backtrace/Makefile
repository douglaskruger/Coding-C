# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
all:	  backtrace stacktrace

backtrace: backtrace.o
	cc backtrace.o -o backtrace

stacktrace: stacktrace.o
	cc stacktrace.o -o stacktrace

stacktrace.o: stacktrace.c
	cc -c stacktrace.c -o stacktrace.o

backtrace.o: backtrace.c
	cc -c backtrace.c -o backtrace.o

clean:
	rm -f backtrace.o backtrace stacktrace.o stacktrace
