#include "Header.h"

ShotgatBullet::ShotgatBullet(D3DXVECTOR2 pos, float theta, float damage, float speed)
	:CBullet(pos, theta, damage, speed, L"enemy")
{
	bulletSpr.LoadAll(L"Assets/Sprites/Weapon/Bullet/Enemy/Shotgat");

	Collider::AABB aabb;
	aabb.min = { -3.5, -3.5 };
	aabb.max = { 3.5, 3.5 };
	bodies.push_back(Collider(this, L"enemyBullet", &aabb));
}

void ShotgatBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void ShotgatBullet::Render()
{
	CBullet::Render();
}

void ShotgatBullet::OnCollision(Collider& coli)
{
}
