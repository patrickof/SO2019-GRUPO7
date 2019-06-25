#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double S, E, r, sigma, T, M;

/***** Calcula a media *****/
double mean(double v[], int tam){

	double total = 0.0;

	for(int i = 0; i< tam; i++)
		total+=v[i];

	return (double)(total/tam);

}

/***** Calcula o desvio padrão *****/
double stddev(double v[], int tam, double media){

	double sum = 0.0 ;

	for(int i = 0; i<tam; i++){

		sum+= pow((v[i] - media),2);

	}

	return (double)sqrt(sum/tam);


}



/***** Realiza o método de Black Scholes *****/
double black_scholes(){

	srand(time(NULL));


	double temp, expoente, result_exp, media, desvio, conf_w, conf_mn, conf_mx;
	
	double trial[(int)M];

	double randomNumber;


	for (int i = 0; i < M; i++){
		
		randomNumber = (double)rand()/(double)RAND_MAX;
		
		expoente = (r - 0.5*pow(sigma,2))*T + sigma*sqrt(T)*randomNumber;

		result_exp = (double)exp(expoente);

		temp = (double)S*result_exp;

		trial[i] = (double)exp((-1)*r*T)*fmax(temp-E,0);

	}

	media = mean(trial, M);

	desvio = stddev(trial, M,  media);

	conf_w = 1.96*desvio/(double)sqrt(M);

	conf_mn = media - conf_w;
	conf_mx = media + conf_w;


    printf("S     %lf\n", S);
    printf("E     %lf\n", E);
    printf("r     %lf\n", r);
    printf("sigma %lf\n", sigma);
    printf("T     %lf\n", T);
    printf("M     %d\n", M);
    printf("Intervalo de confianca: (%lf, %lf)\n", conf_mn, conf_mx);
}


int main(){


	clock_t Ticks[2];

	Ticks[0] = clock();

	/*S = 100.0;
	E = 110.0;
	r = 10.0;
	sigma = 1.0;
	T = 1.0;
	M = 100000;
*/
	scanf("%lf %lf %lf %lf %lf %d", &S, &E, &r, &sigma, &T, &M );


	black_scholes();

	Ticks[1] = clock();

	double Tempo = (Ticks[1]-Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("%g ms.\n", Tempo);

	return 0;



}