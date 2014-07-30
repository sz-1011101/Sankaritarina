#include "Functions.h"
#include <stdlib.h> 
#include <stdio.h>


Functions::Functions()
{
}


Functions::~Functions()
{
}

//Generates a random number between start and, including start and end
int Functions::generateRandomNumber(int start, int end)
{
	int randNum = rand() % (end - start + 1) + start;
	return randNum;
}

//Calculates an generall factor that depends on the provided Framerate
double Functions::calculateFrameFactor(int framerate)
{
	//Be 30 the "optimal" framerate
	return 30.0 / ((double)framerate);
}