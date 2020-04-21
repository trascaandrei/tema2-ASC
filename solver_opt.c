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

void multiplyMatrix2(int N, double* A, double* B, double* C, int sup_inf) {
    int bi, bj, bk;
	int i, j, k;
	double *aPtr, *bPtr, *cPtr;
	int start;

	for(bi = 0; bi < N; bi += BLOCK_SIZE) {
		for(bj = 0; bj < N; bj += BLOCK_SIZE) {
			for(bk = 0; bk < N; bk += BLOCK_SIZE) {
				for(i = 0; i < BLOCK_SIZE; i++) {
					aPtr = A + (bi + i) * N + bk;
					cPtr = C + (bi + i) * N + bj;

					for(j = 0; j < BLOCK_SIZE; j++) {
					    register double sum = 0;
						bPtr = B + bj + j + bk * N;

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

						for(k = start; k != BLOCK_SIZE; k++) {
					         sum += (*aPtr) * (*bPtr);
							 aPtr++;
							 bPtr += N;
						}

						*cPtr = sum;
						cPtr++;
					}
				}
			}
		}
	}
 }

double* my_solver(int N, double *A, double* B) {
	int i, j;
	double *AA = malloc(N * N * sizeof(*AA));
	double *AAB = malloc(N * N * sizeof(*AAB));
	double *BAt = malloc(N * N * sizeof(*BAt));
	double *At = malloc(N * N * sizeof(*At));

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
