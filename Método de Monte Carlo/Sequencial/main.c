//gcc main.c -o main -lm -lgmp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include <math.h>
#include <pthread.h>



void monte_carlo(int n){

	mpf_set_default_prec(256);

	srand(time(NULL));

	mpf_t pi, x, y, s_aux;

	mpf_init(s_aux);
	mpf_init(x);
	mpf_init(y);

	int i, aux, r_aux;


	for(i = 0; i<n; i++){

		mpf_set_d(x,((double)rand()/(double)RAND_MAX));
		mpf_set_d(y,((double)rand()/(double)RAND_MAX));

		mpf_pow_ui(x, x, 2); //x^2
		mpf_pow_ui(y, y, 2); //y^2

		mpf_add(s_aux, x, y); // s_aux = x^2 + y^2

		r_aux = mpf_cmp_d(s_aux,1); //if s_aux>1 "+" 
		
		if(r_aux<=0){ //if s_aux<=1
			aux++;
		}

	}

	mpf_init_set_d(pi, aux); // pi = aux
	mpf_div_ui(pi, pi, i);    // pi = aux/i
	mpf_mul_ui(pi, pi, 4.0); // pi = (aux/i) * 4.0

	gmp_printf("%.6Ff\n", pi);





}

int main(){

	clock_t Ticks[2];

	Ticks[0] = clock();


	monte_carlo(100000000);

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);


	return 0;
}