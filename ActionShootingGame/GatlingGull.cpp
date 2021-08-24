#include "Header.h"

GatlingGull::GatlingGull(D3DXVECTOR2 pos) : CBoss(pos)
{
	ImageSettings();
	SetUnitInfo(15, 30, 1, 0.2f, true, L"enemy");
	CreateCollider(D3DXVECTOR2(-15, 25), D3DXVECTOR2(15, 65));
	patternTime = 8.0f;

	stopRange = 50;

	SetState(BossIdle::GetInstance());
}

void GatlingGull::Update(float deltaTime)
{
	SetBossImage();

	CBoss::Update(deltaTime);
}

void GatlingGull::Render()
{
	CBoss::Render();
}

void GatlingGull::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Boss/";

	bossSprites[BossImage::IDLE_DIR_0].LoadAll(filePath + L"Idle/0.png");
	bossSprites[BossImage::IDLE_DIR_45].LoadAll(filePath + L"Idle/45.png");
	bossSprites[BossImage::IDLE_DIR_90].LoadAll(filePath + L"Idle/90.png");
	bossSprites[BossImage::IDLE_DIR_270].LoadAll(filePath + L"Idle/270.png");
	bossSprites[BossImage::IDLE_DIR_315].LoadAll(filePath + L"Idle/315.png");

	bossSprites[BossImage::WALK_DIR_0].LoadAll(filePath + L"Walk/0");
	bossSprites[BossImage::WALK_DIR_45].LoadAll(filePath + L"Walk/45");
	bossSprites[BossImage::WALK_DIR_90].LoadAll(filePath + L"Walk/90");
	bossSprites[BossImage::WALK_DIR_270].LoadAll(filePath + L"Walk/270");
	bossSprites[BossImage::WALK_DIR_315].LoadAll(filePath + L"Walk/315");

	bossSprites[BossImage::ATTACK].LoadAll(filePath + L"Attack/Attack", 0.05f);
	bossSprites[BossImage::DIE].LoadAll(filePath + L"Die", 0.1f, false);
}

void GatlingGull::CreateBullet(int bulletCnt, float startAngle, float angle)
{
	float bulletInterval = bulletCnt > 1 ? angle / (float)(bulletCnt - 1) : 0;
	for (int i = 0; i < bulletCnt; ++i)
	{
		float theta = (startAngle + bulletInterval * ((float)i - 1)) - bulletInterval / 2; // 0 + 15
		theta = D3DXToRadian(theta);

		nowScene->obm.AddObject(new BasicBullet(pos + D3DXVECTOR2(0, 50), theta, 1, 200, L"enemy"));
	}
}

bool GatlingGull::Pattern1(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	if (Move(deltaTime)) behavior = BossBehavior::WALK;
	else behavior = BossBehavior::IDLE;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x)) + rand() % 30 - 15;

		shootInterval = 0.0f;
		CreateBullet(1, angle, 0);
	}

	return true;
}

bool GatlingGull::Pattern2(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;

	if (Move(deltaTime)) behavior = BossBehavior::WALK;
	else behavior = BossBehavior::IDLE;

	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x)) + rand() % 30 - 15;

		shootInterval = 0.0f;
		CreateBullet(12, angle, 120);
	}

	return true;
}

bool GatlingGull::Pattern3(float deltaTime)
{
	if (patternTime <= 0.0f)
		return false;


	patternTime -= deltaTime;
	shootInterval += deltaTime;

	if (shootInterval >= ability.attackSpeed)
	{
		float angle = D3DXToDegree(atan2(GetDirectionFromPlayer().y, GetDirectionFromPlayer().x)) + rand() % 30 - 15;

		shootInterval = 0.0f;
		CreateBullet(12, angle, 360);
	}

	return true;
}

void GatlingGull::SetPattern(int index)
{
	if (index == 1)
	{
		patternTime = 8.0f;
		ability.attackSpeed = 0.2f;
		behavior = CBoss::BossBehavior::IDLE;
	}

	if (index == 2)
	{
		patternTime = 8.0f;
		ability.attackSpeed = 3.0f;
		behavior = CBoss::BossBehavior::IDLE;
	}
	if (index == 3)
	{
		patternTime = 4.0f;
		ability.attackSpeed = 0.2f;
		behavior = CBoss::BossBehavior::ATTACK;
	}

}

