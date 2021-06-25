#!/bin/sh -x
# ==============================================================================
# Copyright © 2020 Skynet Consulting Ltd.
#
# This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
# copied, or used as the basis for the manufacture or sale of equipment without
# the express written permission of Skynet Consulting Ltd.
# ==============================================================================
# Description:
#   Static Library test
# ==============================================================================

# produces a sum.o object file
gcc -c sum.c -o sum.o  

# Create an archive file
ar -rc libsum.a sum.o

# Show the static library 
nm libsum.a

# Compile and link
gcc main.c -L. -lsum -o main_test

# Execute it.
./main_test
