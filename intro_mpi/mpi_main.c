/* mpi_main.c */

#include "./include/util.h"

int main(int argc, char const * argv[])
{
	int A[M_size][N_size];
	int B[N_size][P_size];
	int C[M_size][P_size];

	int local_A[N_size];
	int local_C[P_size];


	/*********** MPI ***********/
	
	int rank; /* current processor ID (main processor's ID is 0) */
	int size; /* total number of processors */

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank == 0)
	{
		fill_rand((int *)A, M_size, N_size);
		fill_rand((int *)B, N_size, P_size);

		printf("\n----- Matris A -----\n");
        print_matrix((int*)A, M_size, N_size);

        printf("\n----- Matris B -----\n");
        print_matrix((int*)B, N_size, P_size);
	}
	/*_____________________________________________________
	|                                                      |
	|                 Rank 0 (main processor)              |
	|                /      |        |       \             |
	|               /       |        |        \            |
    |              /        |        |         \           |
    |             /         |        |          \          |
    |            /          |        |           \         |
    |         Rank 1      Rank 2   Rank 3      Rank 4      |
	|_____________________________________________________*/

	MPI_Bcast(B, N_size * P_size, MPI_INT, 0, MPI_COMM_WORLD);
	/*
		2. Broadcast of Matrix B 
		- Rank 0 sends matrix `B` to all processes (`Bcast`). 
			└─ Rank 1, Rank 2, Rank 3, Rank 4 (receive `B` matrix)
	*/

	MPI_Scatter(A, N_size, MPI_INT, local_A, N_size, MPI_INT, 0, MPI_COMM_WORLD);
	/*
		1. Scatter Matrix A ────────────────────┐ 
			- Rank 0 (Main Process): Distributes rows of matrix `A` to other processes. 
			- Rank 1: Takes row 1 from matrix `A`. 
			- Rank 2: Takes row 2 from matrix `A`. 
			- Rank 3: Takes row 3 from matrix `A`. 
			- Rank 4: Takes row 4 from matrix `A`.
	*/

	for (int j = 0; j < P_size; j++) 
	{
        local_C[j] = 0;

        for (int k = 0; k < N_size; k++) 
        {
            local_C[j] += local_A[k] * B[k][j];
        }
    }
    /*
	    3. Local Product Calculation 
		    - Rank 1: Multiplies `local_A[1]` by matrix `B` and produces `local_C[1]`. 
		    - Rank 2: Multiplies `local_A[2]` by matrix `B` and produces `local_C[2]`. 
		    - Rank 3: Multiplies `local_A[3]` by matrix `B` and produces `local_C[3]`. 
		    - Rank 4: Multiplies `local_A[4]` by matrix `B` and produces `local_C[4]`.
    */

    MPI_Gather(local_C, P_size, MPI_INT, C, P_size, MPI_INT, 0, MPI_COMM_WORLD);
    /*
	    4. Gathering of Results (Gather) 
	    - Rank 0 (Main Process) gathers the `local_C` results from all processes (`Gather`). 
	    	└─ Rank 1, Rank 2, Rank 3, Rank 4 send their `local_C` results to Rank 0.
    */
    
    if (rank == 0) 
    {
        printf("\n----- Result Matrix C -----\n");
        print_matrix((int*)C, M_size, P_size);
    }
    MPI_Finalize();

	return 0;
}
