#pragma once
class PlayerUI : public Object
{
public:
	Player* player = NULL;

	Sprite heartSpr;
	Sprite emptyHeartSpr;
	RenderInfo heartRI;

	Sprite levelSpr;

	Sprite expBorderSpr;
	Sprite expGaugeSpr;
	RenderInfo expRI;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

