#include "Header.h"

CalcPage::CalcPage()
{
	spr.LoadAll(L"Assets/Sprites/UI/Calc.png");
	spr.bCamera = false;

	layer = 1050;

	time = nowScene->gameTime;
	score = nowScene->score;

	nowScene->obm.AddObject(new Font(L"Number", D3DXVECTOR2(0, 20), time, D3DXVECTOR2(2, 2), 20, layer + 1));
	nowScene->obm.AddObject(new Font(L"Number", D3DXVECTOR2(0, -62), score, D3DXVECTOR2(2, 2), 20, layer + 1));
}

void CalcPage::Update(float deltaTime)
{
	if (time > 0.0f)
	{
		float tempNum = time;
		time -= deltaTime * 100;

		score += tempNum - time;
	}
	else
	{ 
		if (time <= 0.0f)
			time = 0.0f;

		if (Input::GetInstance().KeyDown(VK_SPACE))
		{
			nowScene->score = score;
			Game::GetInstance().ChangeScecne(nowScene->nextScene);
			auto& p = nowScene->player;
			p->ability.hp = p->ability.maxHp;
			PData data;
			data.ability = p->ability;
			data.abilitySpr = p->playerUI->ablitySpr;
			data.bullcnt = p->gun->bulletCnt;
			data.bulletType = p->gun->bulletType;
			data.exp = p->exp;
			data.level = p->level;
			data.shield = p->shield;
			data.ultimateCoolTime = p->ultimateCoolTime;

			PlayerData::GetInstance().SaveData(data);
		}
	}
}

void CalcPage::Render()
{
	spr.Render(RenderInfo{});
}
