/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
 #define NON_TRIANGULAR -1
 #define SUPERIOR       1
 #define INFERIOR       0

// indexul de pe linia i si coloana j a unei matrici liniarizate
// de dimensiune N * N
 int getIndex(int i, int j, int N) {
    return N * i + j;
 }

// C = A * B
 void multiplyMatrix(int N, double *A, double *B, double *C, int sup_inf) {
    int ij;
    int start = 0;
    int i, j, k;

 	for (i = 0; i < N; i++) {
 	    for (j = 0; j < N; j++) {
 	        ij = getIndex(i, j, N);

 	        if (sup_inf == SUPERIOR) {
                if (j < i) {
                     start = i;
                }
 	        } else if (sup_inf == INFERIOR) {
 	            if (j > i) {
                    start = j;
                }
 	        } else {
 	            start = 0;
 	        }

 	        for (k = start; k < N; k++) {
                 C[ij] += A[getIndex(i, k, N)] * B[getIndex(k, j, N)];
 	        }
 	    }
 	}
 }

double* my_solver(int N, double *A, double* B) {
    int i, j;
    double *AA = malloc(N * N * sizeof(double));
    double *AAB = malloc(N * N * sizeof(double));
    double *BAt = malloc(N * N * sizeof(double));
    double *At = malloc(N * N * sizeof(double));

    // transpunem A
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            At[getIndex(i, j, N)] = A[getIndex(j, i, N)];
        }
    }

    multiplyMatrix(N, A, A, AA, SUPERIOR);
    multiplyMatrix(N, AA, B, AAB, SUPERIOR);
    multiplyMatrix(N, B, At, BAt, NON_TRIANGULAR);

	for (i = 0; i < N; i++) {
        for (j = 0 ; j < N; j++) {
    	    BAt[i * N + j] += AAB[i * N + j];
    	}
    }

    free(AA);
    free(AAB);
    free(At);
	return BAt;
}
