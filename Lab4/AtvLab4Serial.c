#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100

int A[M][N];
int x[M];
int y[N];

int main(void) {

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      A[i][j] = 2;
    }
    x[i] = 3;
  }
  
  for (int i = 0; i < N; i++) {
    y[i] = 0;
    for (int j = 0; j < M; j++) {
      y[i] += A[i][j] * x[j];
    }
  }

  return 0;
}
