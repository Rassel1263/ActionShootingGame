#include "Header.h"

BasicBullet::BasicBullet(D3DXVECTOR2 pos, float theta, float damage, float speed, std::wstring ownerTeam)
	:CBullet(pos, theta, damage, speed, ownerTeam)
{
	bulletSpr.LoadAll(L"Assets/Sprites/Weapon/Bullet/bullet1.png");
}

void BasicBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void BasicBullet::Render()
{
	CBullet::Render();
}
