# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	arg_test array c_datatypes get_hostname platform \
	prt_test sleep_test system_calls test_assert test_getchar var_func_arg-1 \
	var_func_arg-2 

arg_test: arg_test.o
	gcc arg_test.o -o arg_test

arg_test.o: arg_test.c
	gcc -c arg_test.c -o arg_test.o

array: array.o
	gcc array.o -o array

array.o: array.c
	gcc -c array.c -o array.o

c_datatypes: c_datatypes.o
	gcc c_datatypes.o -o c_datatypes

c_datatypes.o: c_datatypes.c
	gcc -c c_datatypes.c -o c_datatypes.o

get_hostname: get_hostname.o
	gcc get_hostname.o -o get_hostname

get_hostname.o: get_hostname.c
	gcc -c get_hostname.c -o get_hostname.o

platform: platform.o
	gcc platform.o -o platform

platform.o: platform.c
	gcc -c platform.c -o platform.o

prt_test: prt_test.o
	gcc prt_test.o -o prt_test

prt_test.o: prt_test.c
	gcc -c prt_test.c -o prt_test.o

sleep_test: sleep_test.o
	gcc sleep_test.o -o sleep_test

sleep_test.o: sleep_test.c
	gcc -c sleep_test.c -o sleep_test.o

system_calls: system_calls.o
	gcc system_calls.o -o system_calls

system_calls.o: system_calls.c
	gcc -c system_calls.c -o system_calls.o

test_assert: test_assert.o
	gcc test_assert.o -o test_assert

test_assert.o: test_assert.c
	gcc -c test_assert.c -o test_assert.o

test_getchar: test_getchar.o
	gcc test_getchar.o -o test_getchar

test_getchar.o: test_getchar.c
	gcc -c test_getchar.c -o test_getchar.o

var_func_arg-1: var_func_arg-1.o
	gcc var_func_arg-1.o -o var_func_arg-1

var_func_arg-1.o: var_func_arg-1.c
	gcc -c var_func_arg-1.c -o var_func_arg-1.o

var_func_arg-2: var_func_arg-2.o
	gcc var_func_arg-2.o -o var_func_arg-2

var_func_arg-2.o: var_func_arg-2.c
	gcc -c var_func_arg-2.c -o var_func_arg-2.o

clean:
	rm -f arg_test.o arg_test array.o array \
		c_datatypes.o c_datatypes get_hostname.o get_hostname platform.o platform \
		prt_test.o prt_test sleep_test.o sleep_test system_calls.o system_calls \
		test_assert.o test_assert test_getchar.o test_getchar var_func_arg-1.o var_func_arg-1 \
		var_func_arg-2.o var_func_arg-2 
