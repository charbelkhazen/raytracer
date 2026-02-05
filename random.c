#include "limits.h"

//I use the linear congruential generator method in order to generate a pseudorandom variable
//consists of a simple linear equation, which produce a certain sequence of numbers for each seed.
//decide seed . then f(seed) gives a number and updates seed , now f(updated seed) gives another number in the sequence
//there are certin choices of numbers that produce long sequences that you can use. I rely on this established fact to choose my constants
double rand_uniformDistributionSampling(double a, double b)
{
	static unsigned int seed = 123456789;
	double u;

	//set seed . I use values that are known to produce long sequences . refer to wikipedia . table row2
	seed = seed * 1664525u + 1013904223u;   // LCG step

	// u in (0,1)
	u = (double)seed / (double)UINT_MAX; 

	// map to (a,b)
	return (a + (b - a) * u);
}
