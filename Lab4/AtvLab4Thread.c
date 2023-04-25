#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100

int A[M][N];
int x[N]; 
int y[M];

int thread_count = 3;

void *Pth_mat_vect(void *rank) {
  
  long my_rank = *((long *)rank);
  int i, j;
  int local_m = M / thread_count;
  int my_first_row = my_rank * local_m;
  int my_last_row = (my_rank + 1) * local_m - 1;
  
  for (i = my_first_row; i <= my_last_row; i++) {
    y[i] = 0.0;
    for (j = 0; j < N; j++)
      y[i] += A[i][j] * x[j];
  }
  
  return NULL;
}

int main(void) {
  int i, j;
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      A[i][j] = 3;
    }
    x[i] = 2;
  }
  
  pthread_t thread[thread_count];
  
  for (i = 0; i < thread_count; i++) {
    long *arg = malloc(sizeof(*arg));
    *arg = (long)i;
    pthread_create(&thread[i], NULL, Pth_mat_vect, arg);
    
  }

  for (i = 0; i < thread_count; i++) {
    pthread_join(thread[i], NULL);
  }
  

  return 0;
}
