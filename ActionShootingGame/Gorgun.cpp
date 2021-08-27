#include "Header.h"

Gorgun::Gorgun(D3DXVECTOR2 pos) : CBoss(pos, UnitName::Gorgun)
{
	bossIndex = 1;
	ImageSettings();
	SetUnitInfo(150, 30, 1, 0.2f, false, L"enemy");
	CreateCollider(D3DXVECTOR2(-15, 0), D3DXVECTOR2(15, 65));
	patternTime = 8.0f;

	SetState(BossIdle::GetInstance());
}

void Gorgun::Update(float deltaTime)
{
	SetBossImage();

	CBoss::Update(deltaTime);
}

void Gorgun::Render()
{
	CBoss::Render();
}

void Gorgun::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Boss/Gorgun/";

	bossSprites[BossImage::IDLE_DIR_0].LoadAll(filePath + L"Idle");
	bossSprites[BossImage::PATTERN1].LoadAll(filePath + L"Pattern1");
	bossSprites[BossImage::PATTERN2].LoadAll(filePath + L"Pattern2");
	bossSprites[BossImage::PATTERN3].LoadAll(filePath + L"Pattern3");
	bossSprites[BossImage::DIE].LoadAll(filePath + L"Die", 0.5f, false);
}

void Gorgun::CreateBullet(int bulletCnt, float startAngle, float angle, float speed, BulletType bulletType)
{
	float bulletInterval = bulletCnt > 1 ? angle / (float)(bulletCnt - 1) : 0;
	for (int i = 0; i < bulletCnt; ++i)
	{
		float theta = (startAngle + bulletInterval * ((float)i - 1)) - bulletInterval / 2; // 0 + 15
		theta = D3DXToRadian(theta);

		if (bulletType == BulletType::Basic)
			nowScene->obm.AddObject(new BasicBullet(pos + D3DXVECTOR2(0, 35), theta, 1, speed, L"enemy"));
		if (bulletType == BulletType::Poison)
			nowScene->obm.AddObject(new PoisonBullet(pos + D3DXVECTOR2(0, 35), theta, 1, speed, L"enemy"));
	}
}

bool Gorgun::Pattern1(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x)) + rand() % 30 - 15;

		shootInterval = 0.0f;
		for(int i = 0; i < 2; ++i)
			CreateBullet(6, angle, 90, 200 + i * 50, BulletType::Poison);
		
	}

	return true;
}

bool Gorgun::Pattern2(float deltaTime)
{

	if (patternTime <= 0.0f)
		return false;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x));

		shootInterval = 0.0f;
		CreateBullet(6, angle, 90, 250, BulletType::Basic);
	}

	return true;
}

bool Gorgun::Pattern3(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		shootInterval = 0.0f;

		CreateBullet(12, bulletAngle, 360, 200, BulletType::Basic);
		bulletAngle += 20;
	}

	return true;
}

void Gorgun::SetPattern(int index)
{
	if (index == 1)
	{
		patternTime = 3.0f;
		ability.attackSpeed = 0.5f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN1;
	}

	if (index == 2)
	{

		patternTime = 4.0f;
		ability.attackSpeed = 0.1f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN2;

	}
	if (index == 3)
	{
		patternTime = 5.0f;
		ability.attackSpeed = 0.1f;
		behavior = CBoss::BossBehavior::ATTACK;
		bossImage = CBoss::BossImage::PATTERN3;

	}
}

void Gorgun::SetBossImage()
{
	if (behavior == CBoss::BossBehavior::IDLE) 
		bossImage = BossImage::IDLE_DIR_0;

	if (behavior == CBoss::BossBehavior::WALK)
		bossImage = BossImage::IDLE_DIR_0;

	if (behavior == BossBehavior::DIE)
		bossImage = BossImage::DIE;
}
