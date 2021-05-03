/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"
#include "cblas.h"
/* 
 * Add your BLAS implementation here
 */

#define CblasNoTrans 111
#define CblasTrans 112

double* my_solver(int N, double *A, double *B) {
	int i;

	double* C = calloc(N * N, sizeof(double));
	///C = B * B**t
	// matrix matrix multiply between B and B**t, result in C
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N,
		1, B, N, B, N, 0, C, N);

	// C = A * C = A * B * B**t
	// triangular matrix matrix multiply between A (triangular) and C
	// result in C
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans,
		CblasNonUnit, N, N, 1, A, N, C, N);

	// A = A**t * A
	// triangular matrix matrix multiply between A**t and A, result in A
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans,
		CblasNonUnit, N, N, 1, A, N, A, N);

	// C += A
	for(i = 0 ; i < N * N; i++) {
		C[i] += A[i];
	}

	return C;
}

