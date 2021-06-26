# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	semaphore_child semaphore_example1 semaphore_example2 semaphore_example3 semaphore_example4 \
	semaphore_handler semaphore_parent semaphore_reader semaphore_writer 

semaphore_child: semaphore_child.o
	gcc semaphore_child.o -o semaphore_child

semaphore_child.o: semaphore_child.c
	gcc -c semaphore_child.c -o semaphore_child.o

semaphore_example1: semaphore_example1.o
	gcc semaphore_example1.o -o semaphore_example1

semaphore_example1.o: semaphore_example1.c
	gcc -c semaphore_example1.c -o semaphore_example1.o

semaphore_example2: semaphore_example2.o
	gcc semaphore_example2.o -o semaphore_example2

semaphore_example2.o: semaphore_example2.c
	gcc -c semaphore_example2.c -o semaphore_example2.o

semaphore_example3: semaphore_example3.o
	gcc semaphore_example3.o -o semaphore_example3

semaphore_example3.o: semaphore_example3.c
	gcc -c semaphore_example3.c -o semaphore_example3.o

semaphore_example4: semaphore_example4.o
	gcc semaphore_example4.o -o semaphore_example4

semaphore_example4.o: semaphore_example4.c
	gcc -c semaphore_example4.c -o semaphore_example4.o

semaphore_handler: semaphore_handler.o
	gcc semaphore_handler.o -o semaphore_handler

semaphore_handler.o: semaphore_handler.c
	gcc -c semaphore_handler.c -o semaphore_handler.o

semaphore_parent: semaphore_parent.o
	gcc semaphore_parent.o -o semaphore_parent

semaphore_parent.o: semaphore_parent.c
	gcc -c semaphore_parent.c -o semaphore_parent.o

semaphore_reader: semaphore_reader.o
	gcc semaphore_reader.o -o semaphore_reader

semaphore_reader.o: semaphore_reader.c
	gcc -c semaphore_reader.c -o semaphore_reader.o

semaphore_writer: semaphore_writer.o
	gcc semaphore_writer.o -o semaphore_writer

semaphore_writer.o: semaphore_writer.c
	gcc -c semaphore_writer.c -o semaphore_writer.o

clean:
	rm -f semaphore_child.o semaphore_child semaphore_example1.o semaphore_example1 \
		semaphore_example2.o semaphore_example2 semaphore_example3.o semaphore_example3 semaphore_example4.o semaphore_example4 \
		semaphore_handler.o semaphore_handler semaphore_parent.o semaphore_parent semaphore_reader.o semaphore_reader \
		semaphore_writer.o semaphore_writer 
