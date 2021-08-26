#include "Header.h"

PenetrationBullet::PenetrationBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam)
	:CBullet(pos, theta, damage, speed, ownerTeam)
{
	if (ownerTeam == L"ally")
		bulletSpr.LoadAll(L"Assets/Sprites/Weapon/Bullet/Ally/Penetration");

	Collider::AABB aabb;
	aabb.min = { -3.5, -3.5 };
	aabb.max = { 3.5, 3.5 };
	bodies.push_back(Collider(this, ownerTeam + L"Bullet", &aabb));
}

void PenetrationBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void PenetrationBullet::Render()
{
	CBullet::Render();
}

void PenetrationBullet::OnCollision(Collider& coli)
{

}
