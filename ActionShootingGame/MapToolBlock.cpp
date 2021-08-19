#include "Header.h"
#include "MapToolBlock.h"

MapToolBlock::MapToolBlock(const std::wstring& filePath, D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Tile/" + filePath + L".png");
	spr.bCamera = false;
	mapNum = filePath;

	this->pos = pos;

	Collider::AABB aabb;
	aabb.min = { -9, -9 };
	aabb.max = { 9,  9 };
	bodies.push_back(Collider(this, L"block", &aabb));
}

void MapToolBlock::Update(float deltaTime)
{
}

void MapToolBlock::Render()
{
	spr.Render(RenderInfo{ pos });

	Object::Render();
}
