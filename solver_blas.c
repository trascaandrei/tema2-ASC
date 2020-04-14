/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	double *C = calloc(N * N, sizeof(double));

	cblas_dtrmm('r', 'u', 'n', 'n', N, N, 1.0, A, N, A, N);
	cblas_dgemm('n', 'n', N, N, N, 1.0, A, N, B, N, 0.0, C, N);
	cblas_dtrmm('r', 'u', 't', 'n', N, N, 1.0, A, N, B, N);

	for (int i = 0; i < N; i++) {
	    for (int j = 0 ; j < N; j++) {
	        C[i * N + j] += B[i * N + j];
	    }
	}
	return C;
}
