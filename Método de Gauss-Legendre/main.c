#include <stdio.h>
#include <math.h>


double gauss_legendre(int n){

	int i;
	double a = 1.0, b = 1/sqrt(2), t = 0.25, p = 1.0;
	double a_aux;

	for(i=0; i<n;i++){

		a_aux = (a + b)/2.0; //an+1
		b = sqrt(a*b); //bn+1
		t = t-p*(a-a_aux)*(a-a_aux); //tn+1
		p = 2.0*p; //pn+1

		a = a_aux;
	}

	return (a+b)*(a+b)/(4.0*t);

}


int main(){


	printf("%.6f\n", gauss_legendre(1000) );


	return 0;
}