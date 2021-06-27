# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	serial_demo serial_modbus serial_modbus_humidity serial_modbus_pid 

serial_demo: serial_demo.o
	gcc serial_demo.o -o serial_demo

serial_demo.o: serial_demo.c
	gcc -c serial_demo.c -o serial_demo.o

serial_modbus: serial_modbus.o
	gcc serial_modbus.o -o serial_modbus

serial_modbus.o: serial_modbus.c
	gcc -c serial_modbus.c -o serial_modbus.o

serial_modbus_humidity: serial_modbus_humidity.o
	gcc serial_modbus_humidity.o -o serial_modbus_humidity

serial_modbus_humidity.o: serial_modbus_humidity.c
	gcc -c serial_modbus_humidity.c -o serial_modbus_humidity.o

serial_modbus_pid: serial_modbus_pid.o
	gcc serial_modbus_pid.o -o serial_modbus_pid

serial_modbus_pid.o: serial_modbus_pid.c
	gcc -c serial_modbus_pid.c -o serial_modbus_pid.o

clean:
	rm -f serial_demo.o serial_demo serial_modbus.o serial_modbus \
		serial_modbus_humidity.o serial_modbus_humidity serial_modbus_pid.o serial_modbus_pid 
