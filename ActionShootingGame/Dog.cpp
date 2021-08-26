#include "Header.h"

Dog::Dog(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Dog");
	ri.pivot = { 0.5, 0 };

	this->pos = pos;
	
	Collider::AABB aabb;
	aabb.min = { -5, -5 };
	aabb.max= { 5, 5 };

	bodies.push_back(Collider(this, L"dog", &aabb));
}

void Dog::Update(float deltaTime)
{
	layer = -pos.y + 1010;
	D3DXVECTOR2 dir = { 0, 0 };

	float minLen = 99000009.0f;
	for (auto& enemy : nowScene->enemyVecs)
	{
		D3DXVECTOR2 distance = enemy->pos - pos;
		float length = (distance.x * distance.x + distance.y * distance.y);

		if (minLen > length * length)
		{
			target = enemy;
			minLen = length * length;
		}
	}

	if (target)
	{
		dir = target->pos - pos;
		D3DXVec2Normalize(&dir, &dir);
	}
	
	if(target == NULL)
	{
		dir = nowScene->player->pos - pos;
		D3DXVec2Normalize(&dir, &dir);
	}

	(dir.x > 0) ? ri.scale.x = 1 : ri.scale.x = -1;

	pos += dir * 50 * deltaTime;
	spr.Update(deltaTime);
}

void Dog::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
