/**************************************************************************** 
 * 1-Sept-2022
 * This command takes a standard input stream and then separates the stream 
 * into files based on the year and month.
 * The input file would have lines like:   93519211;20180110080000000;0;1; 
 * Needs to be compiled under the 'wsi' account to have gcc setup
 *  gcc -o split_file split_file.c
 ****************************************************************************/ 

/**************************************************************************** 
 * Header files
 ****************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

/**************************************************************************** 
 * Global Variables
 ****************************************************************************/ 
FILE *g_fp_out[25][15];

/**************************************************************************** 
 * Create the associated directory and then opens the file handles 
 ****************************************************************************/ 
int create_dir(char * base_name, char * base_path)
{
   char dest_file[300];
   int i,j;
   for (i=15; i<25; i++)
   {
      int status = mkdir(base_path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      if (status != 0)
      {
          if (errno != EEXIST)
          {
              printf("Cannot make directory: %s.\nExiting.\n", base_path);
              exit(1);
          }
      }
      for(j=1; j<13; j++)
      {
          sprintf(dest_file, "%s/%s_20%d%02d", base_path, base_name, i,j);
          g_fp_out[i][j] = fopen(dest_file, "a");
      }
   }
}

/**************************************************************************** 
 * Closes the file handles 
 ****************************************************************************/ 
int close_files()
{
   int i,j;
   for (i=15; i<25; i++)
   {
      for(j=1; j<13; j++)
      {
          fclose(g_fp_out[i][j]);
      }
   }
}

/**************************************************************************** 
 * Main Routine
 ****************************************************************************/ 
int main(int argc, char *argv[])
{
   const size_t line_size=300;
   char * line = malloc(line_size);
   char * line_cpy= malloc(line_size);
   char * token;
   int year;
   int month;
   char * year_str = malloc(10);
   char * month_str = malloc(10);
   const char *search = ";";

   /* Check the input arguments */
   if (argc != 3)
   {
       printf("\nMissing parameters. Exiting.\n", argv[0]);
       printf("  %s base_name base_path\n\n",argv[0]);
       printf("Please note that this program 'appends' to existing files and does not over write them.\n");
       printf("Ex. cat ABB_WG_choice_20220831_153135-aaa| %s wg_choice `pwd`\n", argv[0]);
       printf("    cat FILES | %s wg_float /export/sybase/extract_history/processed\n\n", argv[0]);
       exit(1);
   }

   create_dir(argv[1], argv[2]);
   long counter=0;
   while (gets(line) != NULL) 
   { 
      strcpy(line_cpy, line);
      token = strtok(line_cpy, search);
      token = strtok(NULL, search);

      strncpy(year_str, token, 4);
      year_str[4] = '\0';
      year = atoi(year_str);

      strncpy(month_str, token+4, 2);
      month_str[2] = '\0';
      month = atoi(month_str);
      fputs(line, g_fp_out[year-2000][month]);
      fputc('\n', g_fp_out[year-2000][month]);
      if (++counter % 1000000 == 0)
          printf("Processed: %ld millon rows\n", counter/1000000);
   }
   printf("Total Rows Processed: %ld\n", counter);
   
   close_files();
   if (line) free(line);
   if (line_cpy) free(line_cpy);
}
