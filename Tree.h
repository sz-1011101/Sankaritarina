#pragma once
#include "Entity.h"
#include "TreeEnumeration.h"
#include "Graphics.h"
#include "Functions.h"

class Tree : 
	public Entity
{
public:

	Tree(int x, int y, Graphics* graphics, Texture* texture, int const* FRAME_COUNT, int const* FRAME_WIDTH, int const* FRAME_HEIGHT, World* world, bool seeded, int id);
	~Tree();
	virtual void render();
	virtual void calcFrame(int framerate);
	void growTree(int framerate, double rate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();

private:

	TreeEnumeration::TREE_STATE treeState;
	double growth = 0;
	double maxGrothFullSize;
	virtual void updateDebugText();

};

