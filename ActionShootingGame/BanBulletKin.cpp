#include "Header.h"

BanBulletKin::BanBulletKin(D3DXVECTOR2 pos) : CEnemy(pos, UnitName::BANBULLET_KIN)
{
	ImageSettings();
	SetUnitInfo(25, 50, 1, 1, true, L"enemy");
	nowScene->obm.AddObject(gun = new SubMachineGun(this));

	CreateCollider(D3DXVECTOR2(-7, 0), D3DXVECTOR2(7, 10));
	playerDetectionRange = 200;
	stopRange = 100;

	SetState(EnemyIdle::GetInstance());
}

void BanBulletKin::Update(float deltaTime)
{
	SetGunPos();

	CEnemy::Update(deltaTime);
}

void BanBulletKin::Render()
{
	CEnemy::Render();
}

void BanBulletKin::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/BanBulletKin/";

	enemySprites[EnemyImage::IDLE_LEFT].LoadAll(filePath + L"Idle/Left", 0.2f); // LEFT
	enemySprites[EnemyImage::IDLE_RIGHT].LoadAll(filePath + L"Idle/Right", 0.2f); // RIGHT
	enemySprites[EnemyImage::IDLE_UP].LoadAll(filePath + L"Idle/Up", 0.2f);  // UP

	enemySprites[EnemyImage::WALK_LEFT].LoadAll(filePath + L"Walk/Left");
	enemySprites[EnemyImage::WALK_RIGHT].LoadAll(filePath + L"Walk/Right");
	enemySprites[EnemyImage::WALK_UP].LoadAll(filePath + L"Walk/Up");

	enemySprites[EnemyImage::HIT].LoadAll(filePath + L"Hit", 0.05f, false);
	enemySprites[EnemyImage::DIE].LoadAll(filePath + L"Die", 0.1f, false);
}

void BanBulletKin::EnemyAttack(float deltaTime)
{
	restTimer += deltaTime;

	if (restTimer > ability.attackSpeed)
	{
		gun->gunSpr.Update(deltaTime);

		shootTime -= deltaTime;
		if (shootTime <= 0.0f)
		{
			shootTime = 2.0f;
			restTimer = 0.0f;
		}

		if (!gun->gunSpr.bAnimation)
		{
			float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x));

			gun->Shoot(angle, ability.attackPower, team);
			gun->gunSpr.Reset();
		}
	}

}
