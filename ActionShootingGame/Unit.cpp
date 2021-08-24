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

void Unit::SetUnitInfo(float hp, float speed, float attackPower, float attackSpeed, bool holdWeapon, std::wstring team)
{
	bRigidbody = true;
	ability = { hp, hp, speed, attackPower, attackSpeed };
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


bool Unit::CheckDistanceToPlayer(float detectionRange)
{
	return GetDistanceFromTarget(static_cast<GameScene*>(nowScene)->player->pos) < detectionRange * detectionRange;
}

D3DXVECTOR2 Unit::GetDirectionFromPlayer()
{
	if (nowScene->player == NULL)
		return D3DXVECTOR2(0, 0);

	D3DXVECTOR2 distance = (nowScene->player->pos + D3DXVECTOR2(0, 15)) - (pos + D3DXVECTOR2(0, GetNowSprite().textures[0]->info.Height / 2));

	D3DXVec2Normalize(&distance, &distance);

	std::cout << distance.x << "  " << distance.y << std::endl;

	return distance;
}

