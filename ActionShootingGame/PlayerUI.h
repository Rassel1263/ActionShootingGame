#pragma once
class PlayerUI : public Object
{
public:
	Player* player = NULL;

	Sprite border;

	Sprite heartSpr;
	Sprite emptyHeartSpr;
	RenderInfo heartRI;

	Sprite shieldSpr;
	RenderInfo shieldRI;

	Sprite levelSpr;

	Sprite expBorderSpr;
	Sprite expGaugeSpr;
	RenderInfo expRI;

	Sprite ultiFrameSpr;
	Sprite ultiGaugeSpr;
	RenderInfo ultiRI;

	Sprite rollFrameSpr;
	Sprite rollGaugeSpr;
	RenderInfo rollRI;

	std::vector<Sprite> ablitySpr;
	std::vector<RenderInfo> ablityInfo;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void AddAblitySpr(int index);
};

