#include "Header.h"

Gun::Gun(Unit* owner)
{
	this->owner = owner;

	gunSpr.LoadAll(L"Assets/Sprites/Weapon/Gun", 0.15f, false);
	gunRI.pivot = { 0, 0.3 };
}

void Gun::Update(float deltaTime)
{
	gunSpr.Update(deltaTime);
}

void Gun::Render()
{
	gunRI.pos = pos;
	if(owner->holdWeapon) gunSpr.Render(gunRI);
}

void Gun::Shoot()
{
}
