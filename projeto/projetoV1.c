#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  int n;
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

  n = atoi(argv[1]);

for(int i = 1; i<=n;i++){
  mpz_mul_ui(fatorial,fatorial,i);
  mpf_set_z(tmp, fatorial);
  mpf_div(valor,indice,tmp);
  mpf_add(e,e,valor);
}

 gmp_printf("%.10000Ff\n", e);
 mpf_clear(valor);
 mpf_clear(e);
 mpf_clear(indice);
 mpz_clear(fatorial);
 return 1;
}
