#include "Header.h"

Unit::Unit(D3DXVECTOR2 pos)
{
	this->pos = pos;
	renderInfo.pivot = { 0.5, 0};

	unitDir = Unit::DIR::IDLE_DIR_0;

	shadow.LoadAll(L"Assets/Sprites/Unit/shadow.png");
	nowScene->obm.AddObject(gun = new Gun(this));

	layer = 1;
}

void Unit::Update(float deltaTime)
{
	Object::Update(deltaTime);
	sprites.at(unitDir).Update(deltaTime);
}

void Unit::Render()
{
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 1)});

	renderInfo.pos = pos;
	sprites.at(unitDir).Render(renderInfo);

	Object::Render();
}

void Unit::SetUnitInfo(int hp, float speed, float attackPower, float attackSpeed, std::wstring team)
{
	bRigidbody = true;

	ability = { hp, speed, attackPower, attackSpeed };
	this->team = team;
}

void Unit::CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	Collider::AABB aabb;
	aabb.min = min;
	aabb.max = max;
	bodies.push_back(Collider(this, team, &aabb));
}

Sprite& Unit::GetNowSprite()
{
	return sprites.at(unitDir);
}

