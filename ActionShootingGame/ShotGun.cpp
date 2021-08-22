#include "Header.h"

ShotGun::ShotGun(Unit* owner) : CGun(owner)
{
	if (owner->team == L"ally")
		gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun/PlayerGun/ShotGun", 0.08f, false);
	else
		gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun/EnemyGun/ShotGun", 0.08f, false);
}

void ShotGun::Update(float deltaTime)
{
}

void ShotGun::Render()
{
	CGun::Render();
}
