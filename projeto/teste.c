#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void calculaE(mpf_t e, int n, mpz_t fat, mpf_t tmp, mpf_t valor, mpf_t indice){

	for(int i = 1; i<=n; i++){
		mpz_mul_ui(fat,fat,i);
		mpf_set_z(tmp,fat);
		mpf_div(valor,indice,tmp);
		mpf_add(e,e,valor);
	}

}

int main(int argc, char * argv[]){
  mpf_set_default_prec(100000);

  mpf_t valor;
  mpz_t fatorial;
  mpf_t indice;
  mpf_t e;
  mpf_t tmp;

  mpf_init(tmp);
  mpf_init_set_d(e,1.0);
  mpf_init_set_d(indice,1.0);
  mpf_init(valor);
  mpz_init_set_ui(fatorial,1);

  int n = atoi(argv[1]);
  int nthread = atoi(argv[2]);
  pthread_t threads[nthread];
  int thread_arg[nthread];
  int e_thread;

  for(int i = 0; i<=nthread; i++){
	thread_arg[i] = 

 }












  calculaE(e,n,fatorial,tmp,valor,indice);

  gmp_printf("%.1000Ff\n", e);

  mpf_clear(valor);
  mpf_clear(e);
  mpf_clear(indice);
  mpz_clear(fatorial);
  mpf_clear(tmp);
  return 1;
}
