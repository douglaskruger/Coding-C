#!/bin/bash

cat << EOF
# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
EOF

count=0
echo -n "all:	"
for file in `ls -1 *.c | sed -e 's/\.c$//'`
do
count=$((count+1))
if [ $count -gt 5 ]; then echo "\\"; echo -n "	$file "; count=0
else echo -n "$file "
fi
done
echo ""
echo ""

for file in `ls -1 *.c | sed -e 's/\.c$//'`
do
echo "$file: $file.o"
echo "	gcc $file.o -o $file"
echo ""
echo "$file.o: $file.c"
echo "	gcc -c $file.c -o $file.o"
echo ""
done

echo "clean:"
count=0
echo -n "	rm -f "
for file in `ls -1 *.c | sed -e 's/\.c$//'`
do
count=$((count+1))
if [ $count -gt 2 ]; then echo "\\"; echo -n "		$file.o $file "; count=0
else echo -n "$file.o $file "
fi
done
echo ""
