#include "Header.h"

HandGun::HandGun(Unit* owner) : CGun(owner)
{
	if(owner->team == L"ally")
		gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun/PlayerGun/HandGun", 1.0f, false);
	else
		gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun/EnemyGun/HandGun", 0.08f, false);
}

void HandGun::Update(float deltaTime)
{
}

void HandGun::Render()
{
	CGun::Render();
}
