/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: var_func_arg-2.c $";

/*
 * Description:
 *   Second example of variable argument list in c function
 */
#include <stdarg.h> 
#include <stdio.h> 
  
int 
average(int num, ...) 
{ 
	va_list valist; 

	int sum = 0, i; 

	va_start(valist, num); 
	for (i = 0; i < num; i++)
	{  
		sum += va_arg(valist, int);
	}

	va_end(valist); 
	return sum / num; 
} 
  
// Driver code 
int 
main() 
{ 
    printf("Average of {2, 3, 4} = %d\n", average(2, 3, 4)); 
    printf("Average of {3, 5, 10, 15} = %d\n", average(3, 5, 10, 15)); 
    return 0; 
} 
