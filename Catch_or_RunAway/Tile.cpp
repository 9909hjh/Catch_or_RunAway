#include "Tile.h"

Tile::Tile(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Tile::draw()
{
  SDLGameObject::drawFrame();
}

void Tile::update() 
{
	m_rotationAngle += cloudAngspeed;
}
void Tile::clean() {}