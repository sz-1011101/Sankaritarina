//This class handles the Render list used for Rendering a frame
#include "RenderList.h"
#include "RenderListNode.h"
#include <stdio.h>
#define NULL 0

//Constr. for the RenderList
RenderList::RenderList()
{
	first = NULL; //Init first
	last = NULL; //Init last
}

//Denstr. for the RenderList
RenderList::~RenderList()
{
}


//Returns the first node
RenderListNode* RenderList::getFirst()
{
	return first;
}

//Returns the last node
RenderListNode* RenderList::getLast()
{
	return last;
}

//add Renderable to the List
void RenderList::addRenderable(Renderable* mRenderable)
{
	RenderListNode* node = new RenderListNode(mRenderable);
	addNode(node);
}

//Adds a node at the end of the RenderList
void RenderList::addNode(RenderListNode* node)
{
	RenderListNode* currentLast = last;

	if (currentLast == NULL) //list was just initialized
	{
		first = node;
		last = node;
	}
	else
	{
		currentLast->setNext(node); //previous last points to new last
		last = node; //new last element
	}
}

//Removes the first element, returns if successful
bool RenderList::removeFirst()
{

	if (first == NULL) //Return false nothing to remove
	{
		return false;
	}
	else if (first == last) //first is also last
	{
		last = NULL;
	}
		
	RenderListNode* newFirst = first->getNext();
	RenderListNode* oldFirst = first;

	
	first = newFirst;
	oldFirst->~RenderListNode(); //call Deconstructor
	delete oldFirst;
	return true;
}