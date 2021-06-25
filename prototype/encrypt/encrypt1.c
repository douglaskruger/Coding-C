/* =============================================================================
   Copyright © 2020 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
   This simple protoype was build based on the discussion/code on the following 
   website:
   https://stackoverflow.com/questions/20579363/how-to-decrypt-simple-xor-encryptionO
*/

/*==============================================================================
                              System Includes
==============================================================================*/
#include <stdio.h>
#include <string.h>

/*==============================================================================
                              Functions
==============================================================================*/

/* =============================================================================
 * Description:
 *   Generate encrypted/decrypted strings
 * Returns:
 *   void
 * =============================================================================
 */
void 
xor_encrypt(char *key, char *string, int n)
{
    int i;
    int keyLength = strlen(key);
    for( i = 0 ; i < n ; i++ )
    {
        string[i]=string[i]^key[i%keyLength];
    }
}

/* =============================================================================
 * Description:
 *   main routine
 * =============================================================================
 */
int 
main(void) 
{
	char plain[] = "This is plain text";
	char key[] = "ABC123Abcd";
	int n = strlen(plain);

	printf("Original String:\n'%s'\n", plain);

	// encrypt:
	xor_encrypt(key, plain, n);

	printf("Encrypted String: \n");
	for(int ii = 0; ii < n; ii++) 
	{
		// Print the normal character if we can - else print the hex number
		if (plain[ii] > 0x32 && plain[ii] < 0x7F ) 
			printf("%c", plain[ii]);
		else 
			printf(" 0x%02x ", plain[ii]);
	}
	printf("\n");

	// Decrypt the string
	xor_encrypt(key, plain, n);
	printf("Decrypted String:\n'%s'\n", plain);
}
