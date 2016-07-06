# oneSiteForward

##Background
This repository houses a collection of programs that perform simple forward time population genetic simulations of a single site.
The programs simulate a population through either a two epoch population size model (oneSiteForward, oneSiteForwardSelection) or an exponential population size change (oneSiteForwardSelectionExp). These programs do very little-- all they outut is the sojourn time of an allele that has fixed (reached frequency 1.0) in the population. These programs were used in  Kern and Schrider (to appear) to compare output from our program discoal.

## Installing
To install the programs simply clone this git repo, and compile using the following command

```
make all
```
you should then end up with three programs: oneSiteForward, oneSiteForwardSelection, oneSiteForwardSelectionExp.

## Example usage
These programs currently will only output the sojourn time of an allele that has fixed in the population. The user has options to specify population sizes, the number of generations run, and the "window" in which the allele must fix. The window part is option. By way of example lets use the program oneSiteForward to estimate the fixation time of a neutral allele in a population of stationary size N=100 individuals. Theory tells us that the expected fixation time should be approximate 4N = 400.

```
$ ./oneSiteForward 10000000 100 10000 100 400 | awk '{x+=$1;n+=1}END{print x/n}'
398.278
```
Not bad for a simulations that took 14.78 seconds on my desktop. Conditioning on the fixation of an allele in a given range of generations (using the window option) however is more challenging computationally. For that we recommend using a compute cluster.

