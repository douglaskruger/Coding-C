/*
 * Copyright (c) 2024, Skynet Consulting Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Function prototypes
void initArray(int mat[MAX_ROWS][MAX_COLS]);
int readCSV(const char* filename, int mat[MAX_ROWS][MAX_COLS]);
void printArray(int mat[MAX_ROWS][MAX_COLS]);

/**
 * @brief Initializes a 2D array to zero.
 *
 * @param mat The 2D array to initialize.
 */
void initArray(int mat[MAX_ROWS][MAX_COLS])
{
    // Initialize the array to zero
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            mat[i][j] = 0; // Set each element to zero
        }
    }
}

/**
 * @brief Reads a CSV file into a 2D array.
 *
 * @param filename The name of the CSV file to read.
 * @param mat The 2D array to store the data in.
 * @return 0 on success, -1 on failure.
 */
int readCSV(const char* filename, int mat[MAX_ROWS][MAX_COLS])
{
    // Open the file in read mode
    FILE *fstream = fopen(filename, "r");
    if (fstream == NULL)
    {
        printf("\nError: File opening failed.");
        return -1; // Return error code
    }

    char buffer[10240];
    char *record, *line;
    int i = 0, j = 0;

    // Read each line from the file
    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)
    {
        record = strtok(line, ",");
        while (record != NULL)
        {
            mat[i][j++] = atoi(record); // Convert to integer and store in array
            record = strtok(NULL, ",");
        }
        j = 0; // Reset column index
        ++i; // Increment row index
    }

    // Close the file
    fclose(fstream);
    return 0; // Return success code
}

/**
 * @brief Prints the contents of a 2D array.
 *
 * @param mat The 2D array to print.
 */
void printArray(int mat[MAX_ROWS][MAX_COLS])
{
    // Print each row of the array
    for (int i = 0; i < MAX_ROWS; i++)
    {
        printf("Line: %d\n", i);
        for (int j = 0; j < MAX_COLS; j++)
        {
            printf("%d", mat[i][j]); // Print each element
        }
        printf("\n");
    }
}

int main(void)
{
    int mat[MAX_ROWS][MAX_COLS];

    initArray(mat);

    if (readCSV("myFile.csv", mat) != 0)
    {
        return -1; // Return error code
    }

    printArray(mat);

    return 0; // Return success code
}
