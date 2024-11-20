/* util.h */

#ifndef UTIL_H
#define UTIL_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define M_size 4
#define N_size 3
#define P_size 2

void fill_rand(int * matrix, int rows, int cols);
void print_matrix(int * matrix, int rows, int cols);

#endif /* UTIL_H */
