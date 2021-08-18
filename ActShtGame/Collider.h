#pragma once
class Collider
{
public:
	enum class Type
	{
		AABB
	} type;

	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0, 0 };
	}aabb;

	D3DCOLOR color;

	Collider(Object* obj, const std::wstring& tag, const AABB* aabb, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	Object* obj = NULL;
	std::wstring tag;
};

bool IntersectCollider(const Collider& coli1, const Collider& coli2);
bool IntersectAABBAABB(const D3DXVECTOR2& min1, const D3DXVECTOR2& max1, const D3DXVECTOR2& min2, const D3DXVECTOR2& max2);

