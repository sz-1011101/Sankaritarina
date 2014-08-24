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

//Calculates an generell factor that depends on the provided Framerate
double Functions::calculateFrameFactor(int framerate)
{
	//Check if dividing by zero
	if (framerate != 0)
	{
		//Be 30 the "optimal" framerate
		return 30.0 / ((double)framerate);
	}
	else
	{
		return 999999999;
	}
}

//Returns true with the given percentage (0-100)
bool Functions::calculateRandomBoolean(int percentageTrue)
{
	if (generateRandomNumber(1, 100) < percentageTrue)
	{
		return true;
	}
	else
	{
		return false;
	}
}