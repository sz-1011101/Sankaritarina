//This class handles timers
#include "Timer.h"

//Constructor
Timer::Timer()
{
	startTime = SDL_GetTicks();
}

//Destructor
Timer::~Timer()
{
}

//Returns the time
int Timer::getTime()
{
	return SDL_GetTicks() - startTime;
}

//Resets the timer
void Timer::reset()
{
	startTime = SDL_GetTicks();
}