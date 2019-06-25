#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <gmp.h>


mpf_t a, a_aux, b, b_aux, t, t_aux, p, pi;

//Inicialização das variáveis


void *bn (void *args){

	mpf_mul(b, a, b); //b = a*b
	mpf_sqrt(b, b); 

	//gmp_printf("%.6Ff\n", b);


	pthread_exit(NULL);

}
void *an(void *args){

	mpf_add(a_aux, a, b); //aux_a = a+b
	mpf_div_ui(a_aux, a_aux, 2); //aux_a = (a+b)/2

	pthread_exit(NULL);
}





void gauss_legendre(int n){

	mpf_set_default_prec(10000);
	int i;

	pthread_t thread_a[n];
	pthread_t thread_b[n];


	//Inicialização das variáveis
	mpf_init(a);
	mpf_init(a_aux);
	mpf_init(b);
	mpf_init(b_aux);
	mpf_init(t);
	mpf_init(t_aux);
	mpf_init(p);
	mpf_init(pi);

	//Atribuindo óos valores iniciais
	mpf_set_d(a, 1.0);
	mpf_sqrt_ui(b_aux, 2);
	mpf_ui_div(b, 1, b_aux);
	mpf_set_d(t, 0.25);
	mpf_set_d(p, 1.0);

	for(i=0; i<n; i++){

		//an+1
		pthread_create(&(thread_a[i]), NULL, an, NULL);
		//bn+1
		pthread_create(&(thread_b[i]), NULL, bn, NULL);
		
		pthread_join(thread_a[i],NULL);
		pthread_join(thread_b[i],NULL);


		//tn+1
		mpf_sub(t_aux, a, a_aux); // t_aux = a-a_aux;
		mpf_pow_ui(t_aux, t_aux, 2); // t_aux = (a-a_aux)²
		mpf_mul(t_aux, t_aux, p); // t_aux = (a-a_aux)² * p
		mpf_sub(t, t, t_aux); // t = t - (a-a_aux)²*p
		
		//pn+1
		mpf_mul_ui(p, p, 2); // p = p * 2

		mpf_set (a,a_aux); // an+1 = a_aux = (a+b)/2

	}

	mpf_add(a_aux, a, b); // a_aux = a+b;
	mpf_pow_ui(a_aux, a_aux, 2); // a_aux = (a_aux)²
	
	mpf_mul_ui(t_aux, t, 4); // t_aux = t * 4

	mpf_div(pi, a_aux, t_aux);// pi = (a+b)²/(t*4)



	gmp_printf("%.6Ff\n", pi);

	mpf_clear(a); 
	mpf_clear(a_aux);
	mpf_clear(b);
	mpf_clear(b_aux);
	mpf_clear(t);
	mpf_clear(t_aux);
	mpf_clear(p);
	mpf_clear(pi);

}


int main(){

	clock_t Ticks[2];

	Ticks[0] = clock();

	gauss_legendre(10000);

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);

	return 0;
}