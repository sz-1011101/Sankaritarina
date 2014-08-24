#pragma once
#include "Entity.h"
#include "TreeConstants.h"
#include "Graphics.h"
#include "Functions.h"

class Tree : 
	public Entity
{
public:

	Tree(int x, int y, Graphics* graphics, Texture* texture, World* world, bool seeded, int id);
	~Tree();
	virtual void render();
	virtual void calcFrame(int framerate);
	void growTree(int framerate, double rate);
	virtual void proceed(int framerate);
	virtual bool flaggedForRemoval();
	virtual void handleCollisions(int framerate, Map* map);

protected:

	TreeEnumeration::TREE_STATE treeState;
	TreeEnumeration::TREES treeType;
	double growth = 0;
	double maxGrothFullSize;

};

