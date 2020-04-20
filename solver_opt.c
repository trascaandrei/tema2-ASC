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
#define BLOCK_SIZE	   40

int getIndex(int i, int j, int N) {
	return N * i + j;
 }

void multiplyMatrix2(int N, double* a, double* b, double* c, int sup_inf) {
    int bi, bj, bk;
	int i, j, k;
	double *cPtr, *aPtr, *bPtr;

	for(bi = 0; bi < N; bi += BLOCK_SIZE) {
		for(bj = 0; bj < N; bj += BLOCK_SIZE) {
			for(bk = 0; bk < N; bk += BLOCK_SIZE) {
				for(i = 0; i != BLOCK_SIZE; ++i) {
					aPtr = a + (bi + i) * N + bk;
					cPtr = c + (bi + i) * N + bj;

					for(j = 0; j != BLOCK_SIZE; ++j, ++cPtr) {
						bPtr = b + bj + j + bk * N;

						register double sum = 0;

						for(k = 0; k != BLOCK_SIZE; ++k, ++aPtr, bPtr += N) {
							sum += *aPtr * *bPtr;
						}

						*cPtr = sum;
					}
				}
			}
		}
	}
 }

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
	double *AA = calloc(N * N, sizeof(*AA));
	double *AAB = calloc(N * N, sizeof(*AAB));
	double *BAt = calloc(N * N, sizeof(*BAt));
	double *At = calloc(N * N, sizeof(*At));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			At[getIndex(i, j, N)] = A[getIndex(j, i, N)];
		}
	}

	multiplyMatrix2(N, A, A, AA, SUPERIOR);
	multiplyMatrix2(N, AA, B, AAB, SUPERIOR);
	multiplyMatrix2(N, B, At, BAt, NON_TRIANGULAR);

	for (i = 0; i < N; i++) {
		for (j = 0 ; j < N; j++) {
			BAt[i * N + j] += AAB[i * N + j];
		}
	}

	return BAt;
}
