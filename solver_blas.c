/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <string.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
    int i, j;
	double *B2 = malloc(N * N * sizeof(double));
	double *A2 = malloc(N * N * sizeof(double));
	memcpy(A2, A, N * N * sizeof(double));
	memcpy(B2, B, N * N * sizeof(double));

	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans,
	    CblasNonUnit, N, N, 1.0, A, N, A2, N);
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans,
    	    CblasNonUnit, N, N, 1.0, A2, N, B, N);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans,
    	    CblasNonUnit, N, N, 1.0, A, N, B2, N);

	for (i = 0; i < N; i++) {
	    for (j = 0 ; j < N; j++) {
	        B2[i * N + j] += B[i * N + j];
	    }
	}
	free(A2);
	return B2;
}
