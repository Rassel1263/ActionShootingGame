#include "Header.h"

HighPriest::HighPriest(D3DXVECTOR2 pos) : CBoss(pos)
{
	bossIndex = 2;
	ImageSettings();
	SetUnitInfo(200, 30, 1, 0.2f, false, L"enemy");
	CreateCollider(D3DXVECTOR2(-15, 0), D3DXVECTOR2(15, 80));
	patternTime = 8.0f;

	SetState(BossIdle::GetInstance());
}

void HighPriest::Update(float deltaTime)
{
	SetBossImage();

	CBoss::Update(deltaTime);
}

void HighPriest::Render()
{
	CBoss::Render();
}

void HighPriest::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Boss/HighPriest/";

	bossSprites[BossImage::IDLE_DIR_0].LoadAll(filePath + L"Idle");
	bossSprites[BossImage::PATTERN1].LoadAll(filePath + L"Pattern1");
	bossSprites[BossImage::PATTERN2].LoadAll(filePath + L"Pattern2", 0.2f, false);
	bossSprites[BossImage::PATTERN3].LoadAll(filePath + L"Pattern3", 0.1f, false);
	bossSprites[BossImage::DIE].LoadAll(filePath + L"Die", 0.5f, false);
}

void HighPriest::CreateBullet(D3DXVECTOR2 offset, int bulletCnt, float startAngle, float angle, float speed, BulletType bulletType)
{
	float bulletInterval = bulletCnt > 1 ? angle / (float)(bulletCnt - 1) : 0;
	for (int i = 0; i < bulletCnt; ++i)
	{
		float theta = (startAngle + bulletInterval * ((float)i - 1)) - bulletInterval / 2; // 0 + 15
		theta = D3DXToRadian(theta);

		if (bulletType == BulletType::Basic)
			nowScene->obm.AddObject(new BasicBullet(pos + D3DXVECTOR2(0, 40)+  offset, theta, 1, speed, L"enemy"));
		if (bulletType == BulletType::Poison)
			nowScene->obm.AddObject(new PoisonBullet(pos + D3DXVECTOR2(0, 40) +  offset, theta, 1, speed, L"enemy"));
		if (bulletType == BulletType::Penetration)
			nowScene->obm.AddObject(new ShotgatBullet(pos + D3DXVECTOR2(0, 40) + offset, theta, 1, speed));
	}
}

bool HighPriest::Pattern1(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	Move(deltaTime);

	std::default_random_engine rnd(nowScene->rd());

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		std::uniform_int_distribution<int> dis(90, 270);

		shootInterval = 0.0f;
		CreateBullet(D3DXVECTOR2(-37, 10), 1, dis(rnd), 0, 200, BulletType::Basic);
		CreateBullet(D3DXVECTOR2(37, 10), 1, -dis(rnd) + 180, 0, 200, BulletType::Basic);
	}

	return true;
}

bool HighPriest::Pattern2(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	Move(deltaTime);


	if (GetNowSprite().bAnimation) return true;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		shootInterval = 0.0f;
		CreateBullet(D3DXVECTOR2(-37, 10), 1, bulletAngle, 0, 200, BulletType::Basic);
		CreateBullet(D3DXVECTOR2(37, 10), 1, -bulletAngle + 180, 0, 200, BulletType::Basic);

		bulletAngle += 10;
	}

	return true;
}

bool HighPriest::Pattern3(float deltaTime)
{

	D3DXVECTOR2 dir = GetDirectionFromPlayer();
	(dir.x > 0) ? renderInfo.scale.x = 1.0f : renderInfo.scale.x = -1.0f;

	if (!GetNowSprite().bAnimation)
	{
		std::default_random_engine rnd(nowScene->rd());
		std::uniform_int_distribution<int> dis(-10, 10);

		if(dir.x > 0)
			CreateBullet(D3DXVECTOR2(34, 10), 6, 0 + dis(rnd), 90, 400, BulletType::Penetration);
		else
			CreateBullet(D3DXVECTOR2(-34, 10), 6, 180 + dis(rnd), 90, 400, BulletType::Penetration);

		return false;
	}

	return true;

}

void HighPriest::SetPattern(int index)
{
	bulletAngle = 0;
	restTime = 1.0f;

	if (index == 1)
	{
		patternTime = 3.0f;
		ability.attackSpeed = 0.01f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN1;
	}

	if (index == 2)
	{
		patternTime = 3.0f;
		ability.attackSpeed = 0.05f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN2;
		bulletAngle = 60;

	}
	if (index == 3)
	{
		patternTime = 1.0f;
		ability.attackSpeed = 0.0f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN3;
	}
}

void HighPriest::SetBossImage()
{
	if (behavior == CBoss::BossBehavior::IDLE)
		bossImage = BossImage::IDLE_DIR_0;

	if (behavior == CBoss::BossBehavior::WALK)
		bossImage = BossImage::IDLE_DIR_0;

	if (behavior == BossBehavior::DIE)
		bossImage = BossImage::DIE;
}
