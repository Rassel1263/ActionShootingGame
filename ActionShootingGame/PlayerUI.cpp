#include "Header.h"

PlayerUI::PlayerUI(Player* player)
{
	pos = { -220, 110 };

	this->player = player;

	heartSpr.LoadAll(L"Assets/Sprites/UI/Player/Hp/Filled");
	heartSpr.bCamera = false;

	shieldSpr.LoadAll(L"Assets/Sprites/UI/Player/Shield");
	shieldSpr.bCamera = false;

	emptyHeartSpr.LoadAll(L"Assets/Sprites/UI/Player/Hp/empty.png");
	emptyHeartSpr.bCamera = false;

	levelSpr.LoadAll(L"Assets/Sprites/UI/Player/Level");
	levelSpr.bCamera = false;

	expBorderSpr.LoadAll(L"Assets/Sprites/UI/Player/Exp/border.png");
	expBorderSpr.bCamera = false;
	expGaugeSpr.LoadAll(L"Assets/Sprites/UI/Player/Exp/gauge.png");
	expGaugeSpr.bCamera = false;

	border.LoadAll(L"Assets/Sprites/UI/Player/border.png");
	border.bCamera = false;

	ultiFrameSpr.LoadAll(L"Assets/Sprites/UI/Player/Ultimate/Frame.png");
	ultiFrameSpr.bCamera = false;
	ultiGaugeSpr.LoadAll(L"Assets/Sprites/UI/Player/Ultimate/Ultimate.png");
	ultiGaugeSpr.bCamera = false;

	rollFrameSpr.LoadAll(L"Assets/Sprites/UI/Player/Roll/Frame.png");
	rollFrameSpr.bCamera = false;
	rollGaugeSpr.LoadAll(L"Assets/Sprites/UI/Player/Roll/Gauge.png");
	rollGaugeSpr.bCamera = false;

	ablityInfo.resize(5);
	ablityInfo.at(0).pos = { 190, -95 };
	ablityInfo.at(1).pos = { 200, -95 };
	ablityInfo.at(2).pos = { 210, -95 };
	ablityInfo.at(3).pos = { 195, -105 };
	ablityInfo.at(4).pos = { 205, -105 };

	ultiRI.pos = { 175, -100 };
	rollRI.pos = { 155, -100 };

	layer = 1;
}

void PlayerUI::Update(float deltaTime)
{
	expGaugeSpr.widthRatio = player->exp / 100;
	if(player->level > 0 && player->level < 6)
		levelSpr.scene = player->level - 1;

	ultiGaugeSpr.heightRatio = nowScene->player->ultimateTime / nowScene->player->ultimateCoolTime;
	rollGaugeSpr.heightRatio = nowScene->player->rollTime / nowScene->player->rollCoolTime;

	shieldSpr.Update(deltaTime);
}

void PlayerUI::Render()
{
	float pHp = nowScene->player->ability.hp / 2;
	float pMaxHp = nowScene->player->ability.maxHp / 2;

	for (int i = 0; i < pMaxHp; ++i)
	{
		heartRI.pos = pos + D3DXVECTOR2(i * 16 + 20, 6);

		emptyHeartSpr.Render(heartRI);

		if (i < ceil(pHp))
		{
			float minus = pHp - (int)pHp;

			if (i == ceil(pHp - 1) && minus != 0)
				heartSpr.scene = 1;
			else
				heartSpr.scene = 0;

		heartSpr.Render(heartRI);
		}
	}

	for (int i = 0; i < nowScene->player->shield; ++i)
	{
		shieldRI.pos = heartRI.pos + D3DXVECTOR2(i * 16 + 16, 0);

		shieldSpr.Render(shieldRI);
	}

	int cnt = 0;
	for (auto& spr : ablitySpr)
	{
		spr.Render(ablityInfo[cnt]);
		cnt++;
	}

	ultiFrameSpr.Render(ultiRI);
	ultiGaugeSpr.Render(ultiRI);

	rollFrameSpr.Render(rollRI);
	rollGaugeSpr.Render(rollRI);

	levelSpr.Render({pos});
	border.Render({ D3DXVECTOR2(180, -100) });
	expRI.pos = pos + D3DXVECTOR2(36, -8);
	expBorderSpr.Render(expRI);
	expGaugeSpr.Render(expRI);
}

void PlayerUI::AddAblitySpr(int index)
{
	Sprite spr;
	spr.LoadAll(L"Assets/Sprites/UI/Player/Ablity/" + std::to_wstring(index) + L".png");
	spr.bCamera = false;

	ablitySpr.push_back(spr);
}
