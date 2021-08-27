#include "Header.h"

Minimap::Minimap()
{
	border.LoadAll(L"Assets/Sprites/UI/Minimap/border.png");
	border.bCamera = false;

	layer = 150;
}

void Minimap::Update(float deltaTime)
{
	
}

void Minimap::Render()
{
	border.Render({ D3DXVECTOR2(-194.5f, 50.5) });
}

