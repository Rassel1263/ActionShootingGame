#pragma once

class Object;
class Collider
{
public:
	enum class TYPE
	{
		AABB
	} type;
	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0, 0 };
	} aabb;
	Collider(Object* obj, std::wstring tag, const AABB* aabb, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));

	std::wstring tag;
	Object* obj;
	D3DXCOLOR color;
};

bool IntersectCollider(Collider& col1, Collider& col2);
bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2);
