#pragma once
class CalcPage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float time = 0.0f;
	float score = 0.0f;

	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

