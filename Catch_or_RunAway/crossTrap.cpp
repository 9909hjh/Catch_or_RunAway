#include "crossTrap.h"

crossTrap::crossTrap(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void crossTrap::draw()
{
	SDLGameObject::drawFrame();
}

void crossTrap::update()
{
	// 벽을 튕겨 돌아다니는 함정 부분입니다.
	if (m_position.getX() <= 100)
	{
		m_velocity.setX(10);
	}
	else if (m_position.getX() >= 900)
		m_velocity.setX(-10);

	if (m_position.getY() <= 0)
	{
		m_velocity.setY(10);
	}
	else if (m_position.getY() >= 900)
		m_velocity.setY(-10);

	m_rotationAngle += cloudAngspeed;

	SDLGameObject::update();
}

void crossTrap::clean() {}