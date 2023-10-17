#pragma once
#include "SDLGameObject.h"

class XTrap : public SDLGameObject
{
public:
	XTrap(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	int cloudAngspeed = 6;
};