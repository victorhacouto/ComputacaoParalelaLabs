#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void calculaE(int n ,mpf_t* global_res){

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

  int thread_id = omp_get_thread_num();
  int thread_count = omp_get_num_threads();

  int local_n = n/thread_count;

  mpf_t zero;
  mpf_init(zero);

  for(int i = 1; i<=local_n; i++){
	mpz_mul_ui(fatorial,fatorial,i);
	mpf_set_z(tmp,fatorial);
	mpf_div(valor,indice,tmp);
	mpf_add(e,e,valor);
  }

  #pragma omp critical
  mpf_add(*global_res,e,zero);

  mpf_clear(valor);
  mpf_clear(e);
  mpf_clear(indice);
  mpz_clear(fatorial);
  mpf_clear(tmp);
}


int main(int argc, char * argv[]){
  mpf_set_default_prec(100000);

  int n = atoi(argv[1]);

  mpf_t global_res;
  mpf_init(global_res);

  int thread_count = atoi(argv[2]);

  #pragma omp parallel num_threads(thread_count)
  calculaE(n,&global_res);

  gmp_printf("%.30000Ff\n",global_res);
  mpf_clear(global_res);
  return 1;
}
