#include "Header.h"

PlayerUI::PlayerUI(Player* player)
{
	pos = { -220, 110 };

	this->player = player;

	heartSpr.LoadAll(L"Assets/Sprites/UI/Player/Hp/Filled");
	heartSpr.bCamera = false;

	emptyHeartSpr.LoadAll(L"Assets/Sprites/UI/Player/Hp/empty.png");
	emptyHeartSpr.bCamera = false;

	levelSpr.LoadAll(L"Assets/Sprites/UI/Player/Level");
	levelSpr.bCamera = false;

	expBorderSpr.LoadAll(L"Assets/Sprites/UI/Player/Exp/border.png");
	expBorderSpr.bCamera = false;
	expGaugeSpr.LoadAll(L"Assets/Sprites/UI/Player/Exp/gauge.png");
	expGaugeSpr.bCamera = false;
	
	layer = 1;
}

void PlayerUI::Update(float deltaTime)
{
	expGaugeSpr.widthRatio = player->exp / 100;
	if(player->level > 0 && player->level < 6)
		levelSpr.scene = player->level - 1;
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

	levelSpr.Render({pos});
	expRI.pos = pos + D3DXVECTOR2(36, -8);
	expBorderSpr.Render(expRI);
	expGaugeSpr.Render(expRI);
}
