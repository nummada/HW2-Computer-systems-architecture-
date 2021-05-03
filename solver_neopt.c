/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

// multiply an upper triangle matrix with other matrix
double* multiplyASupTrB(double *A, double *B, int N) {

	int i, j, k;

	double* C = calloc(N * N, sizeof(double));

	int start_k = 0; 

	for (i = 0 ; i < N ; i++){
		for (j = 0 ; j < N ; j++){
			C[i * N + j] = 0;
			// skip collumns from A between 0 and start_k
			for (k = start_k ; k < N ; k++){
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
		// increment the start index from k
		start_k += 1;
	}

	return C;
}

//multiply a matrix with the transpose of another
double* multiplyABt(double *A, double *B, int N) {

	int i, j, k;

	double* C = calloc(N * N, sizeof(double));

	for (i = 0 ; i < N ; i++){
		for (j = 0 ; j < N ; j++){
			C[i * N + j] = 0;
			for (k = 0 ; k < N ; k++){
				//switch the indexes from the transposed matrix
				// => B[j][k] instead of B[k][j]
				C[i * N + j] += A[i * N + k] * B[j * N + k];
			}
		}
	}
	
	return C;
}

//multiply a lower triangle matrix with an upper triangle matrix
double* multiplyAInfTrBSupTr(double *A, double *B, int N) {

	int i, j, k;

	double* C = calloc(N * N, sizeof(double));
	int min_j = 0;

	for (i = 0 ; i < N ; i++) {
		int min = i;
		for (j = min_j ; j < N ; j++){
			if (j < i)
				min = j;
			C[i * N + j] = 0;
			// limit k to the minimum number of non zero values
			for (k = 0 ; k < min + 1 ; k++){
				// transpose A: k <=> i
				C[i * N + j] += A[k * N + i] * B[k * N + j];
			}
			// from mathematical calcualtions, the opposite
			// elements are equal
			C[j * N + i] = C[i * N + j];
		}
		min_j += 1;
	}

	return C;
}

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	int i;
	double *C = multiplyASupTrB(A, B, N);
	double *D = multiplyABt(C, B, N);
	double *E = multiplyAInfTrBSupTr(A, A, N);
	for (i = 0 ; i < N * N ; i++) {
		C[i] = D[i] + E[i];
	}
	free(D);
	free(E);

	return C;
}
