# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	numeric_print print_binary_strings printf_decimal_demo sort_string str_util \
	str_util2 str_util3 str_util4 str_util5 string_test 

numeric_print: numeric_print.o
	gcc numeric_print.o -o numeric_print

numeric_print.o: numeric_print.c
	gcc -c numeric_print.c -o numeric_print.o

print_binary_strings: print_binary_strings.o
	gcc print_binary_strings.o -o print_binary_strings

print_binary_strings.o: print_binary_strings.c
	gcc -c print_binary_strings.c -o print_binary_strings.o

printf_decimal_demo: printf_decimal_demo.o
	gcc printf_decimal_demo.o -o printf_decimal_demo

printf_decimal_demo.o: printf_decimal_demo.c
	gcc -c printf_decimal_demo.c -o printf_decimal_demo.o

sort_string: sort_string.o
	gcc sort_string.o -o sort_string

sort_string.o: sort_string.c
	gcc -c sort_string.c -o sort_string.o

str_util: str_util.o
	gcc str_util.o -o str_util

str_util.o: str_util.c
	gcc -c str_util.c -o str_util.o

str_util2: str_util2.o
	gcc str_util2.o -o str_util2

str_util2.o: str_util2.c
	gcc -c str_util2.c -o str_util2.o

str_util3: str_util3.o
	gcc str_util3.o -o str_util3

str_util3.o: str_util3.c
	gcc -c str_util3.c -o str_util3.o

str_util4: str_util4.o
	gcc str_util4.o -o str_util4

str_util4.o: str_util4.c
	gcc -c str_util4.c -o str_util4.o

str_util5: str_util5.o
	gcc str_util5.o -o str_util5

str_util5.o: str_util5.c
	gcc -c str_util5.c -o str_util5.o

string_test: string_test.o
	gcc string_test.o -o string_test

string_test.o: string_test.c
	gcc -c string_test.c -o string_test.o

clean:
	rm -f numeric_print.o numeric_print print_binary_strings.o print_binary_strings \
		printf_decimal_demo.o printf_decimal_demo sort_string.o sort_string str_util.o str_util \
		str_util2.o str_util2 str_util3.o str_util3 str_util4.o str_util4 \
		str_util5.o str_util5 string_test.o string_test 
