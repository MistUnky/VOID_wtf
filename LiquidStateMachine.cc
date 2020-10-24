#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <unistd.h>
#define BRAIN_SIZE  2317 //too small C doesn't work :(
#define BRAIN_SIZEM 2316

//Liquid State Machine: Random Weights, Signal=(0|1), AddSigs*Weights);>1;Fire

//[y*SIZE+x]
std::random_device qdev;
std::uniform_real_distribution<long double> distro( (long double)(-1.0), (long double)(1.0) );
std::uniform_int_distribution<unsigned long long int> ntimer(0, BRAIN_SIZEM);
std::uniform_real_distribution<long double> qinput( (long double)(0.0), (long double)(1.0) );
typedef unsigned long long int ulli;

int main(void) {
	long double *weight = calloc((unsigned)BRAIN_SIZE*BRAIN_SIZE, sizeof(long double));
	long double *fire = calloc((unsigned)BRAIN_SIZE, sizeof(long double));
	for(ulli i = 0; i < BRAIN_SIZE*BRAIN_SIZE; i++) {
		weight[i] = distro(qdev);
	}
	printf("\x1b[2J\x1b[3J\x1b[1;1H");
	while(1) {
		//Inputs
		fire[0] = qinput(qdev);
		fire[1] = qinput(qdev);
		fire[2] = qinput(qdev);
		fire[3] = qinput(qdev);
		fire[4] = qinput(qdev);
		fire[5] = qinput(qdev);
		fire[6] = qinput(qdev);
		fire[7] = qinput(qdev);
		fire[8] = qinput(qdev);
		fire[9] = qinput(qdev);
		//for each neuron !NONONONONO TODO: actually yes, randomly select neuron, time variance simulation :
		//for(ulli i = 0; i < BRAIN_SIZE; i++)
		int i = ntimer(qdev);
		{
			long double my_fire_buf = 0.0;
			//add fires/signals to neuron
			for(ulli j = 0; j < BRAIN_SIZE; j++) {
				//if(!(j == i)) //if not same neuron as firer __>>>>>> TODO: NAH< LETS MAKE IT RECURSIVE!! :) .// away!!!
					my_fire_buf = my_fire_buf + (fire[j] * weight[i*BRAIN_SIZE+j]);
			}
			//fire or don't fire (?)
			printf("Neuron %d: ", i);
			if(my_fire_buf >= 1.0) {
				fire[i] = 1.0;
				printf("Fired!\n"); //TODO: TWO PRINTFS HERE ARE FOR DEBUGGING!
			}
			else {
				fire[i] = 0.0;
				printf("Missd!\n"); //ie NOT Fired!!! TODO: <----
			}
		}
		fflush(stdout);
	}
	free(weight); //lol
}
