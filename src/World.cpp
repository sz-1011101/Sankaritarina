#include "World.h"
#include "Functions.h"
#include "WorldStruct.h"

#include <stdlib.h>
#include <math.h>

/*
Init constants
*/
const Uint8 World::SKY_HOUR_TARGET_RED_COLOR[] = { 2, 2, 2, 2, 17, 52, 235, 241, 138, 84, 138, 100, 90, 60, 36, 022, 90, 102, 255, 255, 117, 27, 12, 7 };
const Uint8 World::SKY_HOUR_TARGET_GREEN_COLOR[] = { 23, 23, 23, 23, 58, 22, 63, 126, 130, 116, 196, 170, 148, 132, 136, 129, 122, 95, 125, 108, 57, 17, 18, 37 };
const Uint8 World::SKY_HOUR_TARGET_BLUE_COLOR[] = { 38, 38, 38, 38, 121, 171, 231, 238, 238, 241, 242, 253, 252, 252, 247, 245, 248, 243, 197, 108, 240, 200, 101, 105 };

const Uint8 World::ENTITY_HOUR_TARGET_RED_COLOR_MOD[] = { 45, 50, 65, 70, 128, 200, 210, 230, 250, 255, 255, 255, 255, 255, 255, 255, 230, 225, 220, 215, 200, 150, 100, 50 };
const Uint8 World::ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[] = { 50, 50, 50, 50, 60, 70, 100, 125, 200, 220, 255, 255, 255, 255, 255, 255, 150, 85, 80, 75, 85, 80, 75, 70 };
const Uint8 World::ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[] = { 100, 100, 100, 90, 85, 80, 90, 100, 150, 200, 255, 255, 255, 255, 255, 255, 200, 150, 75, 70, 90, 95, 100, 100 };

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
				day++;
				hour = 0;
				if (day < 15)
				{
					day++;
				}
				else
				{
					day = 1;
					if (month < 9)
					{
						month++;
					}
					else
					{
						month = 1;
						year++;
					}
				}
			}
		}
	}
	//effects
	calcAndSetSkyColor();
	calcAndSetEntityColorModulation();
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

	strstream << " " << day << "." << month << "." << year;

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

void World::calcAndSetEntityColorModulation()
{
	int deltaR;
	int deltaG;
	int deltaB;

	if (hour != 23)
	{
		deltaR = ENTITY_HOUR_TARGET_RED_COLOR_MOD[hour + 1] - ENTITY_HOUR_TARGET_RED_COLOR_MOD[hour];
		deltaG = ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[hour + 1] - ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[hour];
		deltaB = ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[hour + 1] - ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[hour];

	}
	else
	{
		deltaR = ENTITY_HOUR_TARGET_RED_COLOR_MOD[0] - ENTITY_HOUR_TARGET_RED_COLOR_MOD[23];
		deltaG = ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[0] - ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[23];
		deltaB = ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[0] - ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[23];

	}

	modR = (Uint8)((int)ENTITY_HOUR_TARGET_RED_COLOR_MOD[hour] + ((((double)minute) / 60)*deltaR));
	modG = (Uint8)((int)ENTITY_HOUR_TARGET_GREEN_COLOR_MOD[hour] + ((((double)minute) / 60)*deltaG));
	modB = (Uint8)((int)ENTITY_HOUR_TARGET_BLUE_COLOR_MOD[hour] + ((((double)minute) / 60)*deltaB));
}

/*
Sky Colo getters
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

/*
Color modulation getters
*/
Uint8 World::getRedColorMod()
{
	return modR;
}

Uint8 World::getGreenColorMod()
{
	return modG;
}

Uint8 World::getBlueColorMod()
{
	return modB;
}

//Returns a struct with the suns position
//TODO fix sun positioning
WorldStruct::SUN_POS World::getSunPos()
{
	WorldStruct::SUN_POS sunPos = { 0, 0, };

	const float SUN_POS_POSITION_FACTOR = 1280.0 / 86400.0;
	const float SUN_POS_FACTOR = 0.00000045;
	int x = secound + (60 * minute) + (3600 * hour); //x is the total secound of the day

	sunPos.x = x*SUN_POS_POSITION_FACTOR;
	sunPos.y = std::pow((x - (60 * 60 * 24) / 2), 2)* SUN_POS_FACTOR +900;

	return sunPos;
}