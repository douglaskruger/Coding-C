/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/

/*==============================================================================
  Description:
    Prototype string functions
==============================================================================*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*==============================================================================
                              Functions
==============================================================================*/


/* =============================================================================
 * Description:
 *   Accepts a number and formats to a string with k,M,G
 * =============================================================================
 */
char * 
to_lower(char * inputStr, char * lowerStr)
{
    int i;
    for (i=0; i< strlen(inputStr); i++)
    {
        lowerStr[i] = tolower(inputStr[i]);
    }
    lowerStr[i] = 0;
    return lowerStr;
}

/* =============================================================================
 * Description:
 *   Converts a string to lower case
 * Returns
 *   Pointer to the lower case string
 * =============================================================================
 */
char * 
to_upper(char * inputStr, char * upperStr)
{
    int i;
    for (i=0; i< strlen(inputStr); i++)
    {
        upperStr[i] = toupper(inputStr[i]);
    }
    upperStr[i] = 0;
    return upperStr;
}
    
int main()
{
    char inputStr[100] = "This is a story about the MSM and the configuration FilE. The quick fox.";
    char buffer[100];
 
    printf("\n");
    printf("The original string: '%s'\n", inputStr);
    printf("Lower case: '%s'\n", to_lower(inputStr, buffer));
    printf("Upper case: '%s'\n", to_upper(inputStr, buffer));
    printf("\n");
   
    return  0;
}
