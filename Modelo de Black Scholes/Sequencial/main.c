#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double mean(double v[], int tam){

	double total = 0.0;

	for(int i = 0; i< tam; i++)
		total+=v[i];

	return (total/tam);

}

double stddev(double v[], int tam, double media){

	double sum = 0.0 ;

	for(int i = 0; i<tam; i++){

		sum+= pow((v[i] - media),2);

	}

	return (double)sqrt(sum/tam);


}


double randomNumber(){

	srand(time(NULL));

	return ((double)rand()/(double)RAND_MAX);
}


double black_scholes(double S, double E, double r, double sigma, double T, double M){

	double temp, expoente, result_exp, media, desvio, conf_w, conf_mn, conf_mx;
	
	double trial[(int)M];


	for (int i = 0; i < M; i++){

		expoente = (r - 0.5*pow(sigma,2))*T + sigma*sqrt(T)*randomNumber();

		result_exp = exp(expoente);

		temp = S*result_exp;

		trial[i] = exp((-1)*r*T)*fmax(temp-E,0);

	}

	media = mean(trial, M);

	desvio = stddev(trial, M,  media);

	conf_w = 1.96*desvio/(double)sqrt(M);

	conf_mn = media - conf_w;
	conf_mn = media + conf_mx;


	printf(" Minimo: %.2f e Maximo: %.2f\n", conf_mn, conf_mx );







}

int main(){



	black_scholes(100.0,110.0, 10.0, 1.0, 1.0, 100000);

	return 0;



}