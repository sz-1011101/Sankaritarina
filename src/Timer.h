#pragma once


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

