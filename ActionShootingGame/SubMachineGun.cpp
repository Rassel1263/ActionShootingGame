#include "Header.h"

SubMachineGun::SubMachineGun(Unit* owner) : CGun(owner)
{
	if(owner->team == L"enemy")
		gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun/EnemyGun/SubMachineGun", 0.05f, false);
}

void SubMachineGun::Update(float deltaTime)
{
	CGun::Update(deltaTime);
}

void SubMachineGun::Render()
{
	CGun::Render();
}
