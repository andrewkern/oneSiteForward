#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ranlib.h"
#include <unistd.h>
#include <fcntl.h>

unsigned long devrand(void);
void usage();
float selection(float p, float h, float s);
float haploidSelection(float p, float s);

int main (int argc, const char * argv[]) {
	float p,p0,s;
	int t,reps,gen1,j, maxT;
	int tempX, fixCount;
	int totGen,tmpCnt;
	float sum = 0.0;
	long seed1, seed2;
	int win,i;
	int steps = 26;
	int gN[26] = {1,920,883,846,810,773,736,699,662,626,589,552,515,478,442,405,368,331,294,258,221,184,147,110,74,37};
	int N[26] = {1032,1189,1371,1580,1821,2099,2419,2788,3213,3703,4268,4919,5670,6535,7531,8680,10004,11530,13289,15316,17653,20345,23449,27026,31149,35900};


	
	seed1 = (long) (devrand() % 2147483399);
	seed2 = (long) (devrand() % 2147483399);
	setall(seed1, seed2 );
	
	
	fixCount = 0;
	if( argc < 4){
		usage();
	}
	//locusNumber = atoi(argv[1]);
	reps = atoi(argv[1]);
	gen1 = atoi(argv[2]);
	s = atof(argv[3]);

	if(gen1<0){
		tmpCnt = gen1;
		while(tmpCnt<0){
			gN[0]+=1;
			tmpCnt++;
		}
	}
	else{
		i=0;
		tmpCnt = gen1;
		while(tmpCnt>0){
			gN[i]--;
			tmpCnt--;
			if(gN[i]==0)i+=1;
		}
	}
	
	//set initial p; multiple through by 2 for N
	p0=0.0;
	totGen = 0;
	for(i=0;i<steps;i++){
		N[i] *= 2;
		totGen += gN[i];
		if(p0==0.0 && gN[i]>0){
			p0 = 1.0 / N[i];
			//printf("p0:%f N:%d\n",p0,N[i]);
		}
		//printf("N[%d]:%d gN[%d]:%d\n",i,N[i],i,gN[i]);
	}

	//shift generations
	for(i=0;i<steps;i++){
		if (gN[i]>0)gN[i]++;
	}

	win = totGen;
	if(argc == 5) win = atoi(argv[4]);

	
	maxT = 0;

	while(fixCount < reps){
		//iterate over steps
		t = 1;
		p = p0;
		for(i=0;i<steps;i++){
			//iterate gens population size
			for(j=0;j<gN[i];j++){
			//	printf("p[%d]:%f N:%d\n",t,p,N[i]);
			
				tempX = ignbin(N[i],p);
				p = (float) tempX / N[i];
				p = selection(p,0.5,s);
			//	printf("dip: %lf hap: %lf p:%lf\n",selection(p,0.5,s),haploidSelection(p,s),p);
			//	p = haploidSelection(p,s);
			
				if(p>0.0 && p < 1.0) t+=1;
				else break;
			}
			//printf("outer: p[%d]:%f N:%d\n",t,p,N[i]);
			if(p<=0.0 || p>=1.0) break;
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

float selection(float p, float h, float s){
	float q, wbar, pPrime;
	float w12, w22;
	
	q = 1.0 - p;
	w12 = 1.0 - (h*s);
	w22 = 1.0 - s;
	wbar = (p*p*1) + (2.0*p*q*w12) + (q*q*w22);
	pPrime = ((p*p) + (p*q*w12)) / wbar;
	return(pPrime);
}

float haploidSelection(float p, float s){
	float q, wbar;
	
	q = 1.0 - p;
	wbar = (p*1) + (q*(1-s));
	return(p/wbar);
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
	printf("oneSiteForward reps startGen_beforePresent s window\n");
	printf("window is optional sampling window\n");
	exit(1);
}
