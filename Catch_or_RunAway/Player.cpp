#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "vector"
#include <iostream>
#include "GameOverState.h"


const int CAMERA_X = 40;
const int CAMERA_Y = 40;

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
  SDLGameObject::drawFrame();

  
}

void Player::update()
{
  handleInput();
  checkColl();
  m_acceleration.setY(0.98);
  m_currentFrame = ((SDL_GetTicks() / 100) % 4);
  SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
  m_velocity.setX(0);
  if(m_position.getX() < 0 || m_position.getX() + 33 >= 1080)
  {
    
    if(m_position.getX() < 0)
      m_velocity.setX(5);
    else if(m_position.getX() + 33 >= 720)
      m_velocity.setX(-5);
  }
  else{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
      m_velocity.setX(5);
      SDLGameObject::flip = SDL_FLIP_HORIZONTAL; // 오른쪽으로 이동하게 되면 이미지가 플립되게함.
      
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
      m_velocity.setX(-5);
      SDLGameObject::flip = SDL_FLIP_NONE;
    }
  }
  // 점프
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
  {
    if(isGround)
    {
      m_velocity.setY(-10);
      m_acceleration.setY(0.0098);
      isGround = true;
    }
  }

  //카메라 초점 위치
  TheCamera::Instance()->getCameraRectX((m_position.getX() + (m_width / 2)) - CAMERA_X);
  TheCamera::Instance()->getCameraRectY((m_position.getY() + (m_height / 2))- CAMERA_Y);

  if(TheCamera::Instance()->getCameraRect().x < 0)
  {
    TheCamera::Instance()->getCameraRectX(0);
  }
  if (TheCamera::Instance()->getCameraRect().x > CAMERA_X)
  {
      TheCamera::Instance()->getCameraRectX(CAMERA_X);
  }
  if(TheCamera::Instance()->getCameraRect().y < 0)
  {
    TheCamera::Instance()->getCameraRectY(0);
  }
  if (TheCamera::Instance()->getCameraRect().y > CAMERA_Y)
  {
      TheCamera::Instance()->getCameraRectY(CAMERA_Y);
  }
  // 카메라를 통해서 타일이 화면에 벨런스있게 보여주었습니다.
}

void Player::checkColl()
{
  std::vector<GameObject*> collwall = PlayState::Instance()->getTile(); 

  int plrLeft = m_position.getX();
  int plrRight = plrLeft + m_width;
  int plrTop = m_position.getY();
  int plrBottom = plrTop + m_height;

  for(int i = 0; i < collwall.size(); i++)
  {
    int objectLeft = dynamic_cast<SDLGameObject*>(collwall[i])->GetPos().getX();
    int objectRight = objectLeft + dynamic_cast<SDLGameObject*>(collwall[i])->GetWidth();
    int objectTop = dynamic_cast<SDLGameObject*>(collwall[i])->GetPos().getY();
    int objectBottom = objectTop + dynamic_cast<SDLGameObject*>(collwall[i])->GetHeight();

    if(plrLeft <= objectRight && plrRight >= objectLeft && plrTop <= objectBottom && plrBottom >= objectTop)
    {
      
      if(m_velocity.getY() > 0 && plrBottom >= objectTop && plrBottom < objectBottom && plrLeft != objectRight && plrRight != objectLeft)
      {
       // 아랫부분
        m_position.setY(objectTop - m_height);
        plrTop = m_position.getY();
        plrBottom = plrTop + m_height;

        m_velocity.setY(0);
        m_acceleration.setY(0.0);
        // 이것에 관련된 콜라이더 부분에 닿으면 게임오버 상태로 갑니다.
        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
      }
      else if(m_velocity.getY() < 0 && plrTop <= objectBottom && plrTop > objectTop && plrLeft != objectRight && plrRight != objectLeft)
      {
        // 윗부분.
        m_position.setY(objectBottom);
        plrTop = m_position.getY();
        plrBottom = plrTop + m_height;

        m_velocity.setY(0);
        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
      }
      
      if(m_velocity.getX() < 0 && plrLeft <= objectRight && plrLeft > objectLeft && plrTop != objectBottom && plrBottom != objectTop)
      {
         // 왼쪽부분
        m_position.setX(objectRight);

        m_velocity.setX(0);
        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
      } 
      else if(m_velocity.getX() > 0 && plrRight >= objectLeft && plrRight < objectRight && plrTop != objectBottom && plrBottom != objectTop)
      {
        // 오른쪽부분
        m_position.setX(objectLeft - m_width);

        m_velocity.setX(0);

        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
      }
    }
  }

}