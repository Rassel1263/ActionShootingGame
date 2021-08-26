#include "Header.h"

GatlingGull::GatlingGull(D3DXVECTOR2 pos) : CBoss(pos)
{
	bossIndex = 1;
	ImageSettings();
	SetUnitInfo(100, 30, 1, 0.2f, false, L"enemy");
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
	renderInfo.pos = pos;
	shadow.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 25)});

	if (bHit)
		whiteShader->Render(whiteShader, GetNowSprite(), renderInfo);
	else if (poison)
		poisonShader->Render(poisonShader, GetNowSprite(), renderInfo, D3DXVECTOR4(0.25f, 0.35f, 0.2f, 0.0f));
	else
		GetNowSprite().Render(renderInfo);

	Unit::Render();
}

void GatlingGull::ImageSettings()
{
	std::wstring filePath = L"Assets/Sprites/Unit/Boss/GangGull/";

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

	bossSprites[BossImage::PATTERN3].LoadAll(filePath + L"Attack/Attack", 0.05f);
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
		patternTime = 5.0f;
		ability.attackSpeed = 0.2f;
		behavior = CBoss::BossBehavior::IDLE;
	}

	if (index == 2)
	{
		patternTime = 4.0f;
		ability.attackSpeed = 1.0f;
		behavior = CBoss::BossBehavior::IDLE;
	}
	if (index == 3)
	{
		patternTime = 4.0f;
		ability.attackSpeed = 0.2f;
		behavior = CBoss::BossBehavior::ATTACK;
	}

	restTime = 1.0f;
}

void GatlingGull::SetBossImage()
{
	D3DXVECTOR2 dir = GetDirectionFromPlayer();

	if (behavior == BossBehavior::IDLE)
	{
		if (abs(dir.x) > 0.4)
		{
			if (dir.y > 0.4) bossImage = BossImage::IDLE_DIR_45;
			else if (dir.y < -0.4) bossImage = BossImage::IDLE_DIR_315;
			else bossImage = BossImage::IDLE_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? bossImage = BossImage::IDLE_DIR_90 : bossImage = BossImage::IDLE_DIR_270;
	}

	if (behavior == BossBehavior::WALK)
	{
		if (abs(dir.x) > 0.4)
		{
			if (dir.y > 0.4) bossImage = BossImage::WALK_DIR_45;
			else if (dir.y < -0.4) bossImage = BossImage::WALK_DIR_315;
			else bossImage = BossImage::WALK_DIR_0;

			(dir.x > 0) ? renderInfo.scale.x = 1 : renderInfo.scale.x = -1;
		}
		else if (abs(dir.x <= 0.4))
			(dir.y > 0) ? bossImage = BossImage::WALK_DIR_90 : bossImage = BossImage::WALK_DIR_270;
	}

	if (behavior == BossBehavior::ATTACK)
		bossImage = BossImage::PATTERN3;

	if (behavior == BossBehavior::DIE)
		bossImage = BossImage::DIE;
}

