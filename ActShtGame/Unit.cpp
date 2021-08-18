#include "DXUT.h"
#include "Unit.h"

Unit::Unit(D3DXVECTOR2 pos)
{
	this->pos = pos;

	unitDir = Unit::DIR::IDLE_DIR_0;
}

void Unit::Update(float deltaTime)
{
	sprites.at(unitDir).Update(deltaTime);
}

void Unit::Render()
{
	renderInfo.pos = pos;
	sprites.at(unitDir).Render(renderInfo);
}

bool Unit::Move(float deltaTime)
{
	return false;
}

