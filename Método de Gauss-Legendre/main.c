#include <stdio.h>
#include <math.h>

double an (int n);
double bn (int n);
double tn (int n);
double pn (int n);

double pi (int n); //Calcula o pi com n iterações

double an (int n){

	if (n == 0)
		return 1;

	return (an(n-1)+bn(n-1))/2;


}

double bn (int n){

	if (n == 0)
		return (1/sqrt(2));

	return sqrt(an(n-1)*bn(n-1));

}

double tn(int n){

	if(n == 0)
		return 0.25;

	return tn(n-1) - pn(n-1)*pow(an(n-1)-an(n),2);

}

double pn (int n){

	if (n == 0)
		return 1;

	return 2*pn(n-1);


}

double pi (int n){


	return (pow(an(n+1)+bn(n+1),2))/(4*tn(n+1));

}

int main (){


	printf("%.6f\n",pi(50) );
	return 0;
}
