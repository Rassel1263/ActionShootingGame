#include "Header.h"

Minimap::Minimap()
{
	border.LoadAll(L"Assets/Sprites/UI/Minimap/border.png");
	border.bCamera = false;

	spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/0.png");
	spr.bCamera = false;
	layer = 2;
}

void Minimap::Update(float deltaTime)
{
	if (nowScene->player)
		pos = D3DXVECTOR2(nowScene->player->pos.x / 7, nowScene->player->pos.y / 4);
}

void Minimap::Render()
{
	border.Render({ D3DXVECTOR2(-194.5f, 50.5) });
	spr.Render({pos});
}

void Minimap::AddUnit(D3DXVECTOR2* pos, UnitType unitType)
{
	Sprite spr;
	spr.LoadAll(L"Assets/Sprites/UI/Minimap/Unit/" + std::to_wstring(IntEnum(unitType)) + L".png");
	
	units.push_back(spr);
}
