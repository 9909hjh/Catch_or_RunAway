#pragma once
#include "SDLGameObject.h"

class YTrap : public SDLGameObject
{
public:
	YTrap(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	int cloudAngspeed = 6;
};