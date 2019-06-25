////gcc main.c -o main -lm -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


double *trial;

double S, E, r, sigma, T, M;


void* black_scholes_aux(void *args){

	srand(time(NULL));


	int *n = (int*) args;

	int inicio = (*n)*M/4;

	int fim = inicio + M/4;


	double temp, expoente, max, result_exp;
	

	double randomNumber;



	for (int i = inicio; i < fim; i++){

		randomNumber = ((double)rand())/(double)RAND_MAX;

		expoente = (r - 0.5*pow(sigma,2))*T + sigma*sqrt(T)*randomNumber;

		result_exp = (double)exp(expoente);

		temp = (double)S*result_exp;

		if(temp-E<0)
			max = 0;
		else
			max = temp-E;

		trial[i] = (double)exp((-1)*r*T)*max;

	}

	pthread_exit(NULL);

}

 void black_scholes(){

 	//S = 100.0, E = 110.0, r = 10.0, sigma = 1.0, T = 1.0, M = 100000;
	scanf("%lf %lf %lf %lf %lf %d", &S, &E, &r, &sigma, &T, &M );


 	trial = (double*)malloc(M*sizeof(double));

 	pthread_t threads[4];

 	int entradas[4] = {0, 1, 2, 3};

 	double media, desvio, conf_w, conf_mn, conf_mx;



	pthread_create(&(threads[0]), NULL, black_scholes_aux, &entradas[0]);
	pthread_create(&(threads[1]), NULL, black_scholes_aux, &entradas[1]);
	pthread_create(&(threads[2]), NULL, black_scholes_aux, &entradas[2]);
	pthread_create(&(threads[3]), NULL, black_scholes_aux, &entradas[3]);


	for (int i = 0; i<4; i++)
		pthread_join(threads[i], NULL);




    /***** Média *****/
	double total = 0.0;
	for(int i = 0; i< (int)M; i++){
		//printf("%.5d\n",trial[i]);
		total+=trial[i];
	}
	media = (double)(total/M);

	/***** Desvio Padrão *****/
	double sum = 0.0;
	for(int i = 0; i<(int) M; i++)
		sum+= pow((trial[i] - media),2);
	desvio = (double)sqrt(sum/M);


	conf_w = 1.96*desvio/(double)sqrt(M);

	conf_mn = media - conf_w;
	conf_mx = media + conf_w;

	printf("S     %lf\n", S);
    printf("E     %lf\n", E);
    printf("r     %lf\n", r);
    printf("sigma %lf\n", sigma);
    printf("T     %lf\n", T);
    printf("M     %d\n", M);


	printf("Minimo: %lf e Maximo: %lf\n", conf_mn, conf_mx);

 }

int main(){

	clock_t Ticks[2];

	Ticks[0] = clock();

	black_scholes();

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);

	return 0;



}