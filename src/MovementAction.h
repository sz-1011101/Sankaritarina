#pragma once
#include "Action.h"

class Entity;

class MovementAction :
	public Action
{
public:

	MovementAction(Entity* entity, double x, double y);
	~MovementAction();
	virtual void process(int framerate);

private:

	const int PROCESS_FOR_ITERATIONS = 5;

	double x = 0;
	double y = 0;
};

