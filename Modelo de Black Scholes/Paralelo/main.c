#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


double intervalos[4][2];

double S, E, r, sigma, T, M;

double mean(double v[], int tam){

	double total = 0.0;

	for(int i = 0; i< tam; i++)
		total+=v[i];

	return (double)(total/tam);

}

double stddev(double v[], int tam, double media){

	double sum = 0.0 ;

	for(int i = 0; i<tam; i++){

		sum+= pow((v[i] - media),2);

	}

	return (double)sqrt(sum/tam);


}


double randomNumber(double a){

	srand(time(NULL));

	return ((double)(rand()+a*0.08)/(double)RAND_MAX);
}


void* black_scholes_aux(void *args){

	int *n = (int*) args;

	double temp, expoente, result_exp, media, desvio, conf_w, conf_mn, conf_mx;
	
	double trial[(int)M];


	for (int i = 0; i < (M/4); i++){

		expoente = (r - 0.5*pow(sigma,2))*T + sigma*sqrt(T)*randomNumber(i*(*n));

		result_exp = (double)exp(expoente);

		temp = (double)S*result_exp;

		trial[i] = (double)exp((-1)*r*T)*fmax(temp-E,0);

	}

	media = mean(trial, M);

	desvio = stddev(trial, M,  media);

	conf_w = 1.96*desvio/(double)sqrt(M);

	conf_mn = media - conf_w;
	conf_mx = media + conf_w;

	intervalos[*n][0] = conf_mn;
	intervalos[*n][1] = conf_mx;

	pthread_exit(NULL);

}

 void black_scholes(){

 	S = 100.0, E = 110.0, r = 10.0, sigma = 1.0, T = 1.0, M = 100;

 	pthread_t threads[4];

 	int entradas[4] = {0, 1, 2, 3};

 	double conf_mn_sum = 0;
 	double conf_mx_sum = 0;

 	double conf_mn_medio;
	double conf_mx_medio;




	pthread_create(&(threads[0]), NULL, black_scholes_aux, &entradas[0]);
	pthread_create(&(threads[1]), NULL, black_scholes_aux, &entradas[1]);
	pthread_create(&(threads[2]), NULL, black_scholes_aux, &entradas[2]);
	pthread_create(&(threads[3]), NULL, black_scholes_aux, &entradas[3]);


	for (int i = 0; i<4; i++)
		pthread_join(threads[i], NULL);


	for(int i = 0; i<4; ){
		conf_mn_sum+= intervalos[i][0];
		conf_mx_sum+= intervalos[i][1];
	}

	conf_mn_medio = conf_mn_sum/4.0;
	conf_mx_medio = conf_mx_sum/4.0;

	printf(" Minimo: %.2f e Maximo: %.2f\n", conf_mn_medio, conf_mx_medio);

 }

int main(){

	srand(time(NULL));


	black_scholes();

	return 0;



}