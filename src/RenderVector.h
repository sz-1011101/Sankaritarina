#pragma once
#include <vector>

#include "Renderable.h"

class RenderVector
{
public:

	RenderVector();
	~RenderVector();
	void clearRenderVector();
	void addRenderable(Renderable* renderable);
	std::vector<Renderable*>* getRenderVector();

private:

	std::vector<Renderable*> renderVector;

};

