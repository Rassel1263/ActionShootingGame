#include "Header.h"

PoisonBullet::PoisonBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam)
	:CBullet(pos, theta, damage, speed, ownerTeam)
{
	if (ownerTeam == L"ally")
		bulletSpr.LoadAll(L"Assets/Sprites/Weapon/Bullet/Ally/Poison");
	else
		bulletSpr.LoadAll(L"Assets/Sprites/Weapon/Bullet/Enemy/Poison");

	Collider::AABB aabb;
	aabb.min = { -3.5, -3.5 };
	aabb.max = { 3.5, 3.5 };
	bodies.push_back(Collider(this, ownerTeam + L"Bullet", &aabb));
}

void PoisonBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void PoisonBullet::Render()
{
	CBullet::Render();
}

void PoisonBullet::OnCollision(Collider& coli)
{
	CBullet::OnCollision(coli);

	if (coli.tag != team)
		static_cast<Unit*>(coli.obj)->poison = true;

}
