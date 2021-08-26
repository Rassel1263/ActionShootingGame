#include "Header.h"

Shotgat::Shotgat(D3DXVECTOR2 pos) : CEnemy(pos)
{
	ImageSettings();
	SetUnitInfo(5, 50, 1, 1, false, L"enemy");

	CreateCollider(D3DXVECTOR2(-5, 0), D3DXVECTOR2(5, 10));
	stopRange = 100;
	playerDetectionRange = 100;
}

void Shotgat::Update(float deltaTime)
{
	Move(deltaTime);

	if(CheckDistanceToPlayer(playerDetectionRange) || behavior == EnemyBehavior::WALK)
		EnemyAttack(deltaTime);

	if (behavior == EnemyBehavior::HIT)
		Die();

	GetNowSprite().Update(deltaTime);
	Unit::Update(deltaTime);
}

void Shotgat::Render()
{
	CEnemy::Render();
}

void Shotgat::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/Shotgat/";

	enemySprites[EnemyImage::IDLE_LEFT].LoadAll(filePath + L"Idle", 0.2f); // LEFT

	enemySprites[EnemyImage::WALK_LEFT].LoadAll(filePath + L"AttackBefore", 0.2f, false);

	enemySprites[EnemyImage::DIE].LoadAll(filePath + L"Die", 0.1f, false);
}

void Shotgat::EnemyAttack(float deltaTime)
{
	if (behavior == EnemyBehavior::HIT) return;

	enemyImage = EnemyImage::WALK_LEFT;
	behavior = EnemyBehavior::WALK;
	ability.speed = 0;

	if (!GetNowSprite().bAnimation)
	{
		destroy = true;
		float theta = atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x);
		nowScene->obm.AddObject(new ShotgatBullet(D3DXVECTOR2(pos.x, pos.y + 20), theta, 1, 200));
	}
}

void Shotgat::Die()
{
	enemyImage = EnemyImage::DIE;
	behavior == EnemyBehavior::DIE;

	if (!GetNowSprite().bAnimation)
	{
		nowScene->obm.AddObject(new CEffect(L"ShotgatDie", pos + D3DXVECTOR2(0, 20), 0.05f, D3DXVECTOR2(0.5f, 0.5f)));
		nowScene->AddScore(rand() % 200 + 100);
		nowScene->player->PlusExp(2.5);
		destroy = true;
	}
}
