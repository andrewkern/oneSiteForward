#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ranlib.h"
#include <unistd.h>
#include <fcntl.h>

unsigned long devrand(void);
void usage();

int main (int argc, const char * argv[]) {
	float p;
	int t,reps,N1,gen1,N2,gen2,j, maxT;
	int tempX, temp2N,fixCount;
	int totGen;
	float sum = 0.0;
	long seed1, seed2;
	int win;
	
	seed1 = (long) (devrand() % 2147483399);
	seed2 = (long) (devrand() % 2147483399);
	setall(seed1, seed2 );
	
	fixCount = 0;
	if( argc < 5){
		usage();
	}
	//locusNumber = atoi(argv[1]);
	reps = atoi(argv[1]);
	N1 = atoi(argv[2]);
	gen1 = atoi(argv[3]);
	N2 = atoi(argv[4]);
	gen2 = atoi(argv[5]);
	totGen = gen1 + gen2;
	win = totGen;
	if(argc == 7) win = atoi(argv[6]);

	
	
	maxT = 0;

	while(fixCount < reps){
		if(gen1>0){
			p = 1.0 / (2.0 * N1);
		}
		else{
			p = 1.0/ (2.0 * N2);
		}
		t = 1;
		temp2N = 2 * N1;
		
		//iterate first population size
		for(j=0;j<gen1;j++){
			tempX = ignbin(temp2N,p);
			p = (float) tempX / temp2N;
			if(p>0.0 && p < 1.0) t+=1;
			else break;
		}
		//iterate second population size
		temp2N = 2 * N2;
		for(j=0;j<gen2;j++){
			tempX = ignbin(temp2N,p);
			p = (float) tempX / temp2N;
			if(p>0.0 && p < 1.0) t+=1;
			else break;
		}
		if(p >= 1.0){
			if(totGen - t < win){
				sum+=t;
				if(t>maxT) maxT=t;
				printf("%d\n",t);
			}
		}
		fixCount++;
	}
	
	//printf("mean: %f\n",sum/fixCount);
	//printf("max sojourn: %d\n",maxT);
	
	
	
	
	return(1);
}

unsigned long devrand(void) {
	int fn; 
	unsigned int r; 

	fn = open("/dev/urandom", O_RDONLY); 
	if (fn == -1) 
		exit(-1); /* Failed! */ 
	if (read(fn, &r, 4) != 4) 
		exit(-1); /* Failed! */ 
	close(fn); 
	return r;
}

void usage(){
	printf("oneSiteForward reps N1 gens N2 gens window\n");
	printf("window is optional sampling window\n");
	exit(1);
}
