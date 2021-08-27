#include "Header.h"

MiniUnit::MiniUnit(Unit* unit, Unit::UnitName unitName)
{
	this->unit = unit;

	if (IntEnum(unitName) > 4)
		spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/2.png");
	else if (IntEnum(unitName) > 0)
		spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/1.png");
	else 
		spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/0.png");

	spr.bCamera = false;

	layer = 1050;
}

void MiniUnit::Update(float deltaTime)
{
	if (unit)
		pos = D3DXVECTOR2(-227 + (unit->pos.x / 9.65f), 17 + (unit->pos.y / 8.86f));
}

void MiniUnit::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
