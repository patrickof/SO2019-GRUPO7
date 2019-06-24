#include <stdio.h>
#include <time.h>
#include <gmp.h>

//142654 ms.
void borwein(int n){

	mpf_set_default_prec(1000000);
	
	int i;

	mpf_t a0, a0_aux, a1 ,a1_aux, a2, a2_aux, a3, a3_aux, a4, a4_aux, pi, pi_aux;

	mpf_init_set_d(a0, 0.0625); //a0 = 1/16
	mpf_init_set_d(a1, 4.0);  //a1 = 4.0
	mpf_init_set_d(a2, 2.0);  //a2 = 2.0
	mpf_init_set_d(a3, 1.0);  //a3 = 1.0
	mpf_init_set_d(a4, 1.0);  //a4 = 1.0

	mpf_init(a0_aux);
	mpf_init(a1_aux);
	mpf_init(a2_aux);
	mpf_init(a3_aux);	
	mpf_init(a4_aux);
	mpf_init(pi_aux);

	mpf_init(pi);



	for(i=0; i<n; i++){

		mpf_pow_ui(a0_aux, a0, i); //a0_aux = a0^i

		mpf_div_ui(a1_aux, a1, (8*i+1)); //a1_aux = 4.0/(8i+1)
		mpf_div_ui(a2_aux, a2, (8*i+4)); //a2_aux = 2.0/(8i+4)
		mpf_div_ui(a3_aux, a3, (8*i+5)); //a3_aux = 1.0/(8i+5)
		mpf_div_ui(a4_aux, a4, (8*i+6)); //a4_aux = 1.0/(8i+6)

		mpf_sub(pi_aux, a1_aux, a2_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4)
		mpf_sub(pi_aux, pi_aux, a3_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5)
		mpf_sub(pi_aux, pi_aux, a4_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5) - 1.0/(8i+6)

		mpf_mul(pi_aux, pi_aux, a0_aux); // pi = (1/16)^i * (4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5) - 1.0/(8i+6))

		mpf_add(pi, pi, pi_aux);

	}


	gmp_printf("%.6Ff\n", pi);


}


int main(){

	clock_t Ticks[2];
	
	Ticks[0] = clock();

	borwein(10000);

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);
	return 0;
}