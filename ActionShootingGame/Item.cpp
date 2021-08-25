#include "Header.h"

Item::Item(D3DXVECTOR2 pos)
{
	this->pos = pos;
	itemSpr.LoadAll(L"Assets/Sprites/Item");

	Collider::AABB aabb;
	aabb.min = { -5, -5 };
	aabb.max= { 5, 5 };
	bodies.push_back(Collider(this, L"item", &aabb));
}

void Item::Update(float deltaTime)
{
}

void Item::Render()
{
	itemRI.pos = pos;
	itemSpr.Render(itemRI);

	Object::Render();
}

void Item::OnCollision(Collider& coli)
{
	if (coli.tag == L"ally")
	{
		static_cast<Player*>(coli.obj)->ability.hp++;
		destroy = true;
	}
}
