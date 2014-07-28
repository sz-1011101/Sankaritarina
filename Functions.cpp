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