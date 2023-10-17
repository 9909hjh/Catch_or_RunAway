#include "YTrap.h"

YTrap::YTrap(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void YTrap::draw()
{
	SDLGameObject::drawFrame();
}

void YTrap::update()
{
	if (m_position.getY() <= 200) // 세로로 움직이는 함정입니다.
	{
		m_velocity.setY(10);
	}
	else if (m_position.getY() >= 300)
		m_velocity.setY(-10);

	m_rotationAngle += cloudAngspeed;

	SDLGameObject::update();
}

void YTrap::clean() {}