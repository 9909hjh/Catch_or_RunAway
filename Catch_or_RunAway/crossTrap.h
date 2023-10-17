#pragma once
#include "SDLGameObject.h"

class crossTrap : public SDLGameObject
{
public:
	crossTrap(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	int cloudAngspeed = 6;
};