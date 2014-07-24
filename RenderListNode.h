#pragma once
#include "Renderable.h"
class RenderListNode
{
public:
	RenderListNode(Renderable* mRenderable);
	~RenderListNode();
	RenderListNode* getNext();
	void setNext(RenderListNode* node);
	Renderable* getRenderable();
private:
	Renderable* renderable;
	RenderListNode* next;
};

