#include "Header.h"

ShotgunKin::ShotgunKin(D3DXVECTOR2 pos) : CEnemy(pos, UnitName::SHOTGUN_KIN)
{
	type = ShotgunKinType(rand()% 2);
	ImageSettings();
	SetUnitInfo(30, 50, 1, 1.5f, true, L"enemy");
	nowScene->obm.AddObject(gun = new ShotGun(this));

	CreateCollider(D3DXVECTOR2(-7, 0), D3DXVECTOR2(7, 10));

	playerDetectionRange = 200;
	stopRange = 100;

	gun->angle = 50;
	gun->bulletCnt = 5;

	SetState(EnemyIdle::GetInstance());
}

void ShotgunKin::Update(float deltaTime)
{
	SetGunPos();

	CEnemy::Update(deltaTime);
}

void ShotgunKin::Render()
{
	CEnemy::Render();
}

void ShotgunKin::ImageSettings()
{
	std::wstring filePath;

	if(type == ShotgunKinType::RED)
		filePath = L"Assets/Sprites/Unit/Enemy/ShotgunKin_Red/";

	if(type == ShotgunKinType::BLUE)
		filePath = L"Assets/Sprites/Unit/Enemy/ShotgunKin_Blue/";

	enemySprites[EnemyImage::IDLE_LEFT].LoadAll(filePath + L"Idle/Left", 0.2f); // LEFT
	enemySprites[EnemyImage::IDLE_RIGHT].LoadAll(filePath + L"Idle/Right", 0.2f); // RIGHT
	enemySprites[EnemyImage::IDLE_UP].LoadAll(filePath + L"Idle/Up", 0.2f);  // UP

	enemySprites[EnemyImage::WALK_LEFT].LoadAll(filePath + L"Walk/Left");
	enemySprites[EnemyImage::WALK_RIGHT].LoadAll(filePath + L"Walk/Right");
	enemySprites[EnemyImage::WALK_UP].LoadAll(filePath + L"Walk/Up");

	enemySprites[EnemyImage::DIE].LoadAll(filePath + L"Die", 0.1f, false);
	enemySprites[EnemyImage::HIT].LoadAll(filePath + L"Hit", 0.1f, false);
}

