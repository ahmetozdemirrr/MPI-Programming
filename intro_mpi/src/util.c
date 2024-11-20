/* util.c */

#include "util.h"

void fill_rand(int *matrix, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            matrix[i * cols + j] = rand() % 11;
        }
    }
}

void print_matrix(int * matrix, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%d\t", matrix[i * cols + j]);
        }
        printf("\n");
    }
}
