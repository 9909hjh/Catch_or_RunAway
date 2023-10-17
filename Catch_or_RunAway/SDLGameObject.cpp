#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
  : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0) {
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  flip = SDL_FLIP_NONE;
  m_rotationAngle = 0;
  m_currentRow = 0;
  m_currentFrame = 0;
}
//m_rotationAngle 
void SDLGameObject::drawFrame() {
  TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_rotationAngle, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), flip);
}

void SDLGameObject::draw() {
  TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_rotationAngle, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
  
  m_velocity += m_acceleration;
  m_position += m_velocity;
}