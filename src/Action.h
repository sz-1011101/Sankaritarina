#pragma once

class Entity;

class Action
{
public:

	Action(Entity* entity);
	~Action();
	
	virtual void process(int framerate);
	bool isActionDone();

protected:

	Entity* entity;
	bool actionDone;
	bool actionStarted;
	double amountProcessed;
};

