#pragma once
class Functions
{
public:

	Functions();
	~Functions();
	static int generateRandomNumber(int start, int end);
	static double calculateFrameFactor(int framerate);
	static bool calculateRandomBoolean(int percentageTrue);
};

