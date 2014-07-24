//This class defines a node for the RenderList list
#include "RenderListNode.h"
#include "Renderable.h"
#define NULL 0

//Node Constructor
RenderListNode::RenderListNode(Renderable* mRenderable)
{
	next = NULL;
	renderable = mRenderable;
}

//Node Deconstructor
RenderListNode::~RenderListNode()
{
}

//Getter function for RenderListNode* next
RenderListNode* RenderListNode::getNext() {
	return next;
}

//Setter function for RenderListNode* next
void RenderListNode::setNext(RenderListNode* node)
{
	next = node;
}

//Return the Renderable object
Renderable* RenderListNode::getRenderable()
{
	return renderable;
}