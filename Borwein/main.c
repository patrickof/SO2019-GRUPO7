#include <stdio.h>
#include <math.h>



double borwein (int n){

	double pi= 0;

	int i;

	for(i = 0; i<n; i++){

		pi+=(pow(16,-i))*((4.0/(8.0*i+1.0)) - (2.0/(8.0*i+4.0)) - (1.0/(8.0*i+5.0)) - (1.0/(8.0*i+6.0))); 


	}
	
	return pi;


}



int main(){

	printf("%.6f\n",borwein(1000));

	return 0;
}