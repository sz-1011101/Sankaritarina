#pragma once
#ifdef _MSC_VER
#include <SDL.h>
#else //Linux
#include <SDL2/SDL.h>
#endif

class Timer
{
public:
	Timer();
	~Timer();
	void reset();
	int getTime();
private:
	int startTime;
};

