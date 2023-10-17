#include "SDLGameObject.h"
#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams,
	void(*callback)())
	: SDLGameObject(pParams), m_callback(callback) {}


void MenuButton::draw()
{
	SDLGameObject::draw(); // 다른 클래스에서의 draw와 같은 역할
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::update()
{
	Vector2D* pMousePos =
		TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT)
			&& m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback(); // callback 함수를 호출합니다. 이함수가 없으면 버튼을 눌러도 상태가 바뀌지 않습니다.
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}
