#pragma once
#include "SDLGameObject.h"

class TargetTrap : public SDLGameObject
{
public:
	TargetTrap(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void PlayerTarget();

private:

	int cloudAngspeed = 6;
};