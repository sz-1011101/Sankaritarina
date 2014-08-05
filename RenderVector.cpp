//This class handles the Render list used for Rendering a frame
#include "RenderVector.h"

#include <stdio.h>
#define NULL 0

//Constr. for the RenderVector
RenderVector::RenderVector()
{
	renderVector.reserve(512);
}

//Denstr. for the RenderVector
RenderVector::~RenderVector()
{
	clearRenderVector();
}

//add Renderable to the List
void RenderVector::addRenderable(Renderable* renderable)
{
	renderVector.push_back(renderable);
}

//Clear the vector holding the Renderable objects
void RenderVector::clearRenderVector()
{
	renderVector.clear();
}

//get the vector holding the Renderable pointers
std::vector<Renderable*>* RenderVector::getRenderVector()
{
	return &renderVector;
}