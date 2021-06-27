/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
#include <stdio.h>

int main () {
   char str1[20], str2[30];

   printf("Enter command with arguments");
   scanf("%s", str1);

   printf("Enter your website name: ");
   scanf("%s", str2);

   printf("Entered Name: %s\n", str1);
   printf("Entered Website:%s\n\n", str2);
   
   return(0);
}
