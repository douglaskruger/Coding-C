#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char buffer[10240];
    char *record,*line;
    int mat[100][100];
    int i=0,j=0;

    // Initialize the array to zero
    for (i=0; i<100; i++)
    {
        for (j=0; j<100; j++)
        {
            mat[i][j]=0;
        }
    }

    i=0,j=0;

    FILE *fstream = fopen("myFile.csv","r");
    if(fstream == NULL)
    {
        printf("\n file opening failed ");
        return -1;
    }
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
        // Find the first comma
        record = strtok(line,",");
        while(record != NULL)
        {
            // here you can put the record into the array as per your requirement.
            printf("  record(%d,%d):%s", i, j, record);
            mat[i][j++] = atoi(record);
            record = strtok(NULL,",");
        }
        printf("\n");
        j=0;
        ++i;
    }

    // Dump out the array to the screen
    for (i=0; i<100; i++)
    {
        printf("Line: %d\n", i);
        for (j=0; j<100; j++)
        {
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
