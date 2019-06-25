//gcc main.c -o main -lgmp -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include <math.h>
#include <pthread.h>

#define iteracoes 100000000

mpf_t vector_pi[4];


/***** Thread para calcular o valor de pi *****/
void* monte_carlo_aux(void *args){

	int *n = (int*)args;

	mpf_t pi, x, y, aux, s_aux;


	mpf_init(aux);
	mpf_init(s_aux);
	mpf_init(x);
	mpf_init(y);

	int i, r_aux;

	srand(time(NULL));


	for(i = 0; i<(iteracoes/4); i++){

		
		mpf_set_d(x,((double)rand()/(double)RAND_MAX)); //gera um x aleatório

		mpf_set_d(y,((double)rand()/(double)RAND_MAX)); //gera um y aleatório


		mpf_pow_ui(x, x, 2); //x^2
		mpf_pow_ui(y, y, 2); //y^2

		mpf_add(s_aux, x, y); // s_aux = x^2 + y^2

		r_aux = mpf_cmp_d(s_aux,1); //if s_aux>1 "+" 
		
		if(r_aux<=0){ //if s_aux<=1
			mpf_add_ui(aux, aux, 1.0);
		}

	}


	mpf_init_set(vector_pi[*n], aux); // pi = aux

	mpf_div_ui(vector_pi[*n], vector_pi[*n], (double)i);    // pi = aux/i


	mpf_mul_ui(vector_pi[*n], vector_pi[*n], 4.0); // pi = (aux/i) * 4.0


	mpf_clear(s_aux);
	mpf_clear(x);
	mpf_clear(y);


	pthread_exit(NULL);



}

void monte_carlo(){

	mpf_set_default_prec(256);

	int i;

	int entradas[4] = {0,1,2,3};

	pthread_t threads[4];


	mpf_t pi;  ///valor de pi
	mpf_init(pi);


	pthread_create(&(threads[0]), NULL, monte_carlo_aux, &entradas[0]);
	pthread_create(&(threads[1]), NULL, monte_carlo_aux, &entradas[1]);
	pthread_create(&(threads[2]), NULL, monte_carlo_aux, &entradas[2]);
	pthread_create(&(threads[3]), NULL, monte_carlo_aux, &entradas[3]);


	for(i = 0; i<4; i++)
		pthread_join(threads[i], NULL);



	for(i = 0; i<4; i++)
		mpf_add(pi, pi, vector_pi[i]);

	mpf_div_ui(pi, pi, 4.0); //tira uma média dos 4 valores possíveis de pi

	gmp_printf("%.6Ff\n", pi);

	mpf_clear(pi);



}

int main(){

clock_t Ticks[2];

	Ticks[0] = clock();

	monte_carlo();

	for (int i = 0; i<4; i++)
		mpf_clear(vector_pi[i]);
	
	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);



	return 0;
}