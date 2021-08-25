#include "Header.h"

CGun::CGun(Unit* owner)
{
	this->owner = owner;
	gunRI.pivot = { 0, 0.3 };

	bulletType = BulletType::Basic;

	layer = owner->layer;
}

void CGun::Update(float deltaTime)
{
}

void CGun::Render()
{
	gunRI.pos = pos;
	if(owner->holdWeapon) gunSpr.Render(gunRI);
}

void CGun::Shoot(float angle, float damage, std::wstring team)
{
	startAngle = angle;
	this->angle = 30;
	float bulletInterval = bulletCnt > 1 ? this->angle / (float)(bulletCnt - 1) : 0;
	for (int i = 0; i < bulletCnt; ++i)
	{
		float theta = (startAngle + bulletInterval * ((float)i - 1)) - bulletInterval / 2; // 0 + 15
		theta = D3DXToRadian(theta);

		CreateBullet(theta);
	}
}

void CGun::CreateBullet(float theta)
{
	if(bulletType == BulletType::Basic)
		nowScene->obm.AddObject(new BasicBullet(pos, theta, owner->ability.attackPower, 200, owner->team));

	if(bulletType == BulletType::Poison)
		nowScene->obm.AddObject(new PoisonBullet(pos, theta, owner->ability.attackPower, 200, owner->team));
}
