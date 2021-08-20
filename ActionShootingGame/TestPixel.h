#pragma once
class TestPixel : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	TestPixel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

