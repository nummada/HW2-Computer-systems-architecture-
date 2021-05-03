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

	for (i = 0 ; i < N ; i++) {
		double *orig_pa = &A[i * N + start_k];
		for (j = 0 ; j < N ; j++){
			double *pa = orig_pa;
			double *pb = &B[start_k * N + j];
			register double suma = 0.0;
			// skip collumns from A between 0 and start_k
			for (k = start_k ; k < N ; k++){
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			C[i * N + j] = suma;
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

	for (i = 0 ; i < N ; i++) {
		double *orig_pa = &A[i * N];
		double *orig_pb = &B[0];
		for (j = 0 ; j < N ; j++){
			double *pb = orig_pb;
			double *pa = orig_pa;
			register double suma = 0.0;
			for (k = 0 ; k < N ; k++) {
				suma += *pa * *pb;
				pa++;
				pb++;
			}
			orig_pb += N;
			C[i * N + j] = suma;
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
		for (j = min_j ; j < N ; j++) {
			register double suma = 0.0;
			if (j < i)
				min = j;
			// limit k to the minimum number of non zero values
			for (k = 0 ; k < min + 1 ; k++) {
				suma += A[k * N + i] * B[k * N + j];
			}
			// from mathematical calcualtions, the opposite
			// elements are equal
			C[i * N + j] = suma;
			C[j * N + i] = suma;
		}
		min_j += 1;
	}
	
	return C;
}


/*
 * Add your optimized implementation here
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
