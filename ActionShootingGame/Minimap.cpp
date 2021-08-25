#include "Header.h"

Minimap::Minimap()
{
	border.LoadAll(L"Assets/Sprites/UI/Minimap/border.png");
	border.bCamera = false;

	layer = 2;
}

void Minimap::Update(float deltaTime)
{
}

void Minimap::Render()
{
	border.Render({ D3DXVECTOR2(-194.5f, 50.5) });
}

void Minimap::AddUnit(D3DXVECTOR2* pos, UnitType unitType)
{
	Sprite spr;
	spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/" + std::to_wstring(IntEnum(unitType)) + L".png");
	

}
