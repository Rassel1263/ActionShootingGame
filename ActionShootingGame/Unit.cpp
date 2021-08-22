#include "Header.h"

Unit::Unit(D3DXVECTOR2 pos)
{
	this->pos = pos;
	renderInfo.pivot = { 0.5, 0};
	holdWeapon = true;

	shadow.LoadAll(L"Assets/Sprites/Unit/shadow.png");

	layer = 1;
}

void Unit::Update(float deltaTime)
{
	Object::Update(deltaTime);
}

void Unit::Render()
{
	Object::Render();
}

void Unit::SetUnitInfo(int hp, float speed, float attackPower, float attackSpeed, bool holdWeapon, std::wstring team)
{
	bRigidbody = true;
	ability = { hp, speed, attackPower, attackSpeed };
	this->holdWeapon = holdWeapon;
	this->team = team;
}

void Unit::CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	Collider::AABB aabb;
	aabb.min = min;
	aabb.max = max;
	bodies.push_back(Collider(this, team, &aabb));
}

float Unit::GetDistanceFromTarget(D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = targetPos - pos;

	return distance.x* distance.x + distance.y * distance.y;
}


