#pragma once
#include "Tree.h"

class Appletree :
	public Tree
{
public:
	Appletree(int x, int y, Graphics* graphics, Texture* texture, World* world, bool seeded, int id);
	~Appletree();
};

