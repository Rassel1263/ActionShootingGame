#include "DXUT.h"
#include "Collider.h"

Collider::Collider(Object* obj, const std::wstring& tag, const AABB* aabb, D3DCOLOR color)
{
	if (aabb)
	{
		type = Type::AABB;
		this->aabb = *aabb;
	}

	this->tag = tag;
	this->obj = obj;
	this->color = color;
	obj->bCollider = true;
}

bool IntersectCollider(const Collider& coli1, const Collider& coli2)
{
	if (coli1.obj && coli2.obj)
	{
		return IntersectAABBAABB(coli1.obj->pos + coli1.aabb.min, coli1.obj->pos + coli1.aabb.max, coli2.obj->pos + coli2.aabb.min, coli2.obj->pos + coli2.aabb.max);
	}

	return false;
}

bool IntersectAABBAABB(const D3DXVECTOR2& min1, const D3DXVECTOR2& max1, const D3DXVECTOR2& min2, const D3DXVECTOR2& max2)
{
	return (min1.x < max2.x) && (min2.x < max1.x) && (min1.y < max2.y) && (min2.y < max1.y);
}
