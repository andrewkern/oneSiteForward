CC = gcc
#CC = icc
CFLAGS =  -Wall

all:	oneSiteForward oneSiteForwardSelection oneSiteForwardSelectionExp 

oneSiteForward: oneSiteForward.c 
	gcc oneSiteForward.c ranlibComplete.c -o oneSiteForward -lm -O2 -Wall

oneSiteForwardSelection: oneSiteForwardSelection.c 
	gcc oneSiteForwardSelection.c ranlibComplete.c -o oneSiteForwardSelection -lm -O2 -Wall

oneSiteForwardSelectionExp: oneSiteForwardSelectionExp.c 
	gcc oneSiteForwardSelectionExp.c ranlibComplete.c -o oneSiteForwardSelectionExp -lm -O2 -Wall
	
clean:
	rm -f oneSiteForward oneSiteForwardSelection oneSiteForwardSelectionExp *.o