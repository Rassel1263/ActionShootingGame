#pragma once
class GameOver : public Object
{
public:
	Sprite bg;
	Sprite font;

	RenderInfo ri;

	GameOver();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

