#include "gmp.h"
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

void calculaE(int n ,mpf_t* global_res, int thread_count){

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

  int local_n_comeco = (n/thread_count) * thread_id;
  int local_n_fim = (n/thread_count) * (thread_id + 1);

  mpf_t zero;
  mpf_init(zero);

  int aux = 1;

  #pragma omp parallel for
  for(int i = local_n_comeco; i<=local_n_fim; i++){
	mpz_mul_ui(fatorial,fatorial,aux);
	mpf_set_z(tmp,fatorial);
	mpf_div(valor,indice,tmp);
	mpf_add(e,e,valor);
	aux++;
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

  mpf_set_default_prec(500000);
  int n = atoi(argv[1]);



  mpf_t global_res;
  mpf_init(global_res);

  int thread_count = atoi(argv[2]);

 #pragma omp parallel num_threads(thread_count)
  calculaE(n,&global_res,omp_get_num_threads());

  gmp_printf("%.125000Ff\n",global_res);
  mpf_clear(global_res);
  return 1;
}

