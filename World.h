#pragma once
#include "WorldEnumeration.h"

#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL.h>

class World
{
public:

	World();
	~World();
	WorldEnumeration::WORLD_SEASONS getCurrentSeason();
	int getHour();
	int getMinute();
	void advance(int framerate);
	std::string getTimeString();
	Uint8 getRedSkyColor();
	Uint8 getGreenSkyColor();
	Uint8 getBlueSkyColor();

private:

	const double SECOUND_INCREASE_FACTOR = 50;
	static const Uint8 SKY_HOUR_TARGET_RED_COLOR[24];
	static const Uint8 SKY_HOUR_TARGET_GREEN_COLOR[24];
	static const Uint8 SKY_HOUR_TARGET_BLUE_COLOR[24];

	WorldEnumeration::WORLD_SEASONS currentSeason = WorldEnumeration::WORLD_SEASON_SPRING;
	int year = 1;
	int month = 1;
	int day = 1;
	int hour = 12;
	int minute = 0;
	double secound = 0;
	

	Uint8 skyR;
	Uint8 skyG;
	Uint8 skyB;

	void calcAndSetSkyColor();
};

