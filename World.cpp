#include "World.h"
#include "Functions.h"

#include <stdlib.h>

/*
Init constants
*/
const Uint8 World::SKY_HOUR_TARGET_RED_COLOR[] = { 2, 2, 2, 2, 17, 52, 235, 241, 138, 84, 138, 87, 44, 12, 36, 22, 90, 102, 255, 255, 117, 27, 12, 7 };
const Uint8 World::SKY_HOUR_TARGET_GREEN_COLOR[] = { 23, 23, 23, 23, 58, 22, 63, 126, 130, 116, 196, 170, 148, 132, 136, 129, 122, 95, 125, 108, 57, 17, 18, 37 };
const Uint8 World::SKY_HOUR_TARGET_BLUE_COLOR[] = { 38, 38, 38, 38, 121, 171, 231, 238, 238, 241, 242, 253, 252, 252, 247, 245, 248, 243, 197, 108, 240, 200, 101, 105 };

//World constructor
World::World()
{
	hour = Functions::generateRandomNumber(6, 17);


	//Set initial sky color
	skyR = SKY_HOUR_TARGET_RED_COLOR[hour];
	skyG = SKY_HOUR_TARGET_GREEN_COLOR[hour];
	skyB = SKY_HOUR_TARGET_BLUE_COLOR[hour];
}

//World destructor
World::~World()
{
}

//Returns the current season
WorldEnumeration::WORLD_SEASONS World::getCurrentSeason()
{
	return currentSeason;
}

//Returns the current hour(range 0-23)
int World::getHour()
{
	return hour;
}

//Returns the current minute(range 0-59)
int World::getMinute()
{
	return minute;
}

//Advance in time in the world
void World::advance(int framerate)
{
	//advance in time
	if (secound < 59)
	{
		//the secound increases depending on the framerate
		secound = secound + SECOUND_INCREASE_FACTOR*Functions::calculateFrameFactor(framerate);
	}
	else
	{
		secound = 0;
		if (minute < 59)
		{
			minute++;
		}
		else
		{
			minute = 0;
			if (hour < 23)
			{
				hour++;
			}
			else
			{
				hour = 0;
				day++;
				hour = 0; //Just increment hours
			}
		}
	}
	//effects
	calcAndSetSkyColor();
}

std::string World::getTimeString()
{
	std::stringstream strstream;
	strstream.str("");
	//Make a nice readable stringstream
	if (hour < 10)
	{
		strstream << "0" << hour;
	}
	else
	{
		strstream << hour;
	}

	strstream << ":";

	if (minute < 10)
	{
		strstream << "0" << minute;
	}
	else
	{
		strstream << minute;
	}

	return strstream.str();
}

//Calculate and set the color modulation according to the daylight
void World::calcAndSetSkyColor()
{
	int deltaR;
	int deltaG;
	int deltaB;

	if (hour != 23)
	{
		deltaR = SKY_HOUR_TARGET_RED_COLOR[hour + 1] - SKY_HOUR_TARGET_RED_COLOR[hour];
		deltaG = SKY_HOUR_TARGET_GREEN_COLOR[hour + 1] - SKY_HOUR_TARGET_GREEN_COLOR[hour];
		deltaB = SKY_HOUR_TARGET_BLUE_COLOR[hour + 1] - SKY_HOUR_TARGET_BLUE_COLOR[hour];
	}
	else
	{
		deltaR = SKY_HOUR_TARGET_RED_COLOR[0] - SKY_HOUR_TARGET_RED_COLOR[23];
		deltaG = SKY_HOUR_TARGET_GREEN_COLOR[0] - SKY_HOUR_TARGET_GREEN_COLOR[23];
		deltaB = SKY_HOUR_TARGET_BLUE_COLOR[0] - SKY_HOUR_TARGET_BLUE_COLOR[23];
	}

	//Calculate offset and add
	skyR = (Uint8)((int)SKY_HOUR_TARGET_RED_COLOR[hour] + ((((double)minute) / 60)*deltaR));
	skyG = (Uint8)((int)SKY_HOUR_TARGET_GREEN_COLOR[hour] + ((((double)minute) / 60)*deltaG));
	skyB = (Uint8)((int)SKY_HOUR_TARGET_BLUE_COLOR[hour] + ((((double)minute) / 60)*deltaB));
}

/*
Color modulation getters
*/
Uint8 World::getRedSkyColor()
{
	return skyR;
}

Uint8 World::getGreenSkyColor()
{
	return skyG;
}
Uint8 World::getBlueSkyColor()
{
	return skyB;
}
