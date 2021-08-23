#include "Header.h"

BulletKim::BulletKim(D3DXVECTOR2 pos) : CEnemy(pos)
{
	ImageSettings();
	SetUnitInfo(15, 50, 1, 1, true, L"enemy");
	nowScene->obm.AddObject(gun = new HandGun(this));

	CreateCollider(D3DXVECTOR2(-7, 0), D3DXVECTOR2(7, 10));
	playerDetectionRange = 200;
	stopRange = 100;
}

void BulletKim::Update(float deltaTime)
{
	SetGunPos();

	CEnemy::Update(deltaTime);
}

void BulletKim::Render()
{
	CEnemy::Render();
}

void BulletKim::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/BulletKim/";

	enemySprites[EnemyImage::IDLE_LEFT].LoadAll(filePath + L"Idle/Left", 0.2f); // LEFT
	enemySprites[EnemyImage::IDLE_RIGHT].LoadAll(filePath + L"Idle/Right", 0.2f); // RIGHT
	enemySprites[EnemyImage::IDLE_UP].LoadAll(filePath + L"Idle/Up", 0.2f);  // UP

	enemySprites[EnemyImage::WALK_LEFT].LoadAll(filePath + L"Walk/Left");
	enemySprites[EnemyImage::WALK_RIGHT].LoadAll(filePath + L"Walk/Right");
	enemySprites[EnemyImage::WALK_UP].LoadAll(filePath + L"Walk/Up");

	enemySprites[EnemyImage::HIT].LoadAll(filePath + L"Hit", 0.05f, false);
	enemySprites[EnemyImage::DIE].LoadAll(filePath + L"Die", 0.1f, false);
}
