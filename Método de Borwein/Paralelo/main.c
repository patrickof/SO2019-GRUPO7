//gcc main.c -o main -lgmp -lpthread

#include <stdio.h>
#include <pthread.h>
#include <gmp.h>

#define iteracoes 10000


mpf_t vector_pi[4]; // Guarda os 4 valores de pi


/***** Thread que calcula o valor de pi *****/
void *borwein_aux(void *args){

	int *n = (int *) args;

	int inicial = (iteracoes * (*n)) / 4;
	int final = inicial + iteracoes/4;

	printf("thread: %d, inicio: %d, fim: %d\n", *n, inicial, final); 

	mpf_t a0, a0_aux, a1 ,a1_aux, a2, a2_aux, a3, a3_aux, a4, a4_aux, pi_aux, pi_thread;

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

	mpf_init(pi_thread);




	for(int i = inicial; i<final; i++){

		mpf_pow_ui(a0_aux, a0, i); //a0_aux = a0^i

		mpf_div_ui(a1_aux, a1, (8*i+1)); //a1_aux = 4.0/(8i+1)
		mpf_div_ui(a2_aux, a2, (8*i+4)); //a2_aux = 2.0/(8i+4)
		mpf_div_ui(a3_aux, a3, (8*i+5)); //a3_aux = 1.0/(8i+5)
		mpf_div_ui(a4_aux, a4, (8*i+6)); //a4_aux = 1.0/(8i+6)

		mpf_sub(pi_aux, a1_aux, a2_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4)
		mpf_sub(pi_aux, pi_aux, a3_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5)
		mpf_sub(pi_aux, pi_aux, a4_aux); // pi = 4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5) - 1.0/(8i+6)

		mpf_mul(pi_aux, pi_aux, a0_aux); // pi = (1/16)^i * (4.0/(8i+1) - 2.0/(8i+4) - 1.0/(8i+5) - 1.0/(8i+6))

		mpf_add(pi_thread, pi_thread, pi_aux);

	}

	mpf_init_set(vector_pi[*n], pi_thread);

	mpf_clear(a0); 
	mpf_clear(a0_aux);
	mpf_clear(a1);
	mpf_clear(a1_aux);
	mpf_clear(a2);
	mpf_clear(a2_aux);
	mpf_clear(a3);
	mpf_clear(a3_aux);
	mpf_clear(a4);
	mpf_clear(a4_aux);
	mpf_clear(pi_aux);
	mpf_clear(pi_thread);

	pthread_exit(NULL);



}


/***** Função que cria as 4 threads *****/
void borwein(int n){

	int i;
	
	pthread_t threads[4];

	int entradas[4] = {0,1,2,3};
	
	mpf_t pi;

	mpf_init(pi);


	pthread_create(&(threads[0]), NULL, borwein_aux, &entradas[0]);
	pthread_create(&(threads[1]), NULL, borwein_aux, &entradas[1]);
	pthread_create(&(threads[2]), NULL, borwein_aux, &entradas[2]);
	pthread_create(&(threads[3]), NULL, borwein_aux, &entradas[3]);


	for(i = 0; i<4; i++)
		pthread_join(threads[i], NULL);



	for(i =0; i<4; i++)
		mpf_add(pi, pi, vector_pi[i]);

		gmp_printf("%.6Ff\n", pi);

		mpf_clear(pi);





}


int main(){

	clock_t Ticks[2];

	Ticks[0] = clock();

	mpf_set_default_prec(1000000);

	borwein(iteracoes);

	for (int i = 0; i<4; i++)
		mpf_clear(vector_pi[i]);
	

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);

	return 0;
}