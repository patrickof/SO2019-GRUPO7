#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double monte_carlo(int n){
	
	srand(time(NULL));

	double pi, x, y;

	int i, aux = 0;


	for (i = 0; i<n; i++){

		x = ((double)rand()/(double)RAND_MAX); 
		y = ((double)rand()/(double)RAND_MAX);

		if((pow(x,2)+pow(y,2))<=1){
			aux +=1; 

		}
	}
	
	pi =  ((double)aux/(double)i)*4.0;

	return pi;


}


int main(){

	printf("%.6f\n", monte_carlo(100000000));
	return 0;
}