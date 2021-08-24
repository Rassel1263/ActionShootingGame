#pragma once
class BossUI : public Object
{
public:
	CBoss* boss = NULL;

	Sprite hpSpr;
	Sprite hpBorderSpr;
	RenderInfo hpRI;

	BossUI(CBoss* boss);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

