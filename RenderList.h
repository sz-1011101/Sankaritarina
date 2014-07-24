#pragma once
#include "RenderListNode.h"
class RenderList
{
public:
	RenderList();
	~RenderList();
	RenderListNode* getFirst();
	RenderListNode* getLast();
	
	bool removeFirst();
	void addRenderable(Renderable* mRenderable);
private:
	RenderListNode* first;
	RenderListNode* last;

	void addNode(RenderListNode* node);
};

