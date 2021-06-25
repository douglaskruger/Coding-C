/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: test_assert.c $";

/*
 * Description:
 *   Assert prototype 
 */
#include <assert.h>
#include <stdio.h>

int 
main () 
{
	char str[100];
	 
	int a, b;

	printf("\n");
	printf("Input two integers to divide\n");
	scanf("%d%d", &a, &b);
	assert(b != 0);
	printf("%d/%d = %.2f\n", a, b, a/(float)b);
	printf("\n");

	printf("Enter an integer value 10 or greater: ");
	scanf("%d", &a);
	assert(a >= 10);
	printf("Integer entered is %d\n", a);
	printf("\n");

	printf("Enter string: ");
	scanf("%s", str);
	assert(str != NULL);
	printf("String entered is: %s\n", str);
	printf("\n");

	return(0);
}
