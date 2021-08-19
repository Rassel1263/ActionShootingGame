#include "Header.h"

Unit::Unit(D3DXVECTOR2 pos)
{
	this->pos = pos;

	bRigidbody = true;
	unitDir = Unit::DIR::IDLE_DIR_0;

	layer = 1;
}

void Unit::Update(float deltaTime)
{
	Object::Update(deltaTime);
	sprites.at(unitDir).Update(deltaTime);
}

void Unit::Render()
{
	renderInfo.pos = pos;
	sprites.at(unitDir).Render(renderInfo);
}

Sprite& Unit::GetNowSprite()
{
	return sprites.at(unitDir);
}

