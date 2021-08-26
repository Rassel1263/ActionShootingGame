#include "Header.h"

BossUI::BossUI(CBoss* boss)
{
	this->boss = boss;

	hpSpr.LoadAll(L"Assets/Sprites/UI/Boss/gauge");
	hpSpr.bCamera = false;
	hpBorderSpr.LoadAll(L"Assets/Sprites/UI/Boss/border");
	hpBorderSpr.bCamera = false;

	hpSpr.color.a = 0.0f;
	hpBorderSpr.color.a = 0.0f;

	pos = { 0, -120 };

	layer = 1050;
}

void BossUI::Update(float deltaTime)
{
	if (boss->ability.hp <= 0)
	{
		hpBorderSpr.color.a -= deltaTime;
		
		if (hpBorderSpr.color.a <= 0.0f)
			destroy = true;
	}

	if (hpSpr.color.a <= 1.0f)
	{
		hpSpr.color.a += deltaTime;
		hpBorderSpr.color.a = hpSpr.color.a;
	}

	hpSpr.widthRatio = boss->ability.hp / boss->ability.maxHp;

	hpSpr.Update(deltaTime);
}

void BossUI::Render()
{
	hpRI.pos = pos;

	hpBorderSpr.Render(hpRI);
	hpSpr.Render(hpRI);
}
