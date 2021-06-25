#!/bin/sh
# ==============================================================================
# Copyright © 2019 Skynet Consulting Ltd.
#
# This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
# copied, or used as the basis for the manufacture or sale of equipment without
# the express written permission of Skynet Consulting Ltd.
# ==============================================================================
# Description:
#   Demonstrate shared and dynamic libaries 
# ==============================================================================

# create directories if necessary
mkdir -p shared static bin

# Compile the main.c to be used by both examples
gcc -c main.c  -o bin/main.o

# ==============================================================================
# STATIC Example
# ==============================================================================
# Create the object files for the static library (without -fPIC)
#
gcc -c add.c    -o static/add.o
gcc -c answer.c -o static/answer.o

# Create static library
ar rcs static/libadd.a static/add.o static/answer.o

# Statically link the library
gcc   bin/main.o  -Lstatic -ladd -o bin/main_static

# ==============================================================================
# Shared Example
# ==============================================================================
# object files for shared libraries need to be compiled as position independent
# code (-fPIC) because they are mapped to any position in the address space.
#
gcc -c -fPIC add.c    -o shared/add.o
gcc -c -fPIC answer.c -o shared/answer.o

# Shared library
gcc -shared shared/add.o shared/answer.o -o shared/libadd.so

#
#  In order to create a shared library, position independent code
#  must be generated. This can be achieved with `-fPIC` flag when
#  c-files are compiled.
#
#  If the object files are created without -fPIC (such as when the static object files are produces), then
#      gcc -shared bin/static/add.o bin/static/answer.o -o bin/shared/libtq84.so
#  produces this error:
#     /usr/bin/ld: bin/tq84.o: relocation R_X86_64_PC32 against symbol `gSummand' can not be used when making a shared object; recompile with -fPIC
#
gcc  bin/main.o -Lshared -ladd -o bin/main_shared

# Run the results
echo "*********************************************************************************"
echo "Static library"
echo "*********************************************************************************"
bin/main_static

echo "*********************************************************************************"
echo "Shared library"
echo "*********************************************************************************"
export LD_LIBRARY_PATH=`pwd`/shared:$LD_LIBRARY_PATH
bin/main_shared
