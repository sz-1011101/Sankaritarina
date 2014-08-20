#pragma once

class Entity;
class Controller;

class EntityControllerPair
{
public:

	EntityControllerPair(Entity* entity, Controller* controller);
	~EntityControllerPair();
	Entity* getEntity();
	Controller* getController();

private:

	Entity* entity;
	Controller* controller;

};

