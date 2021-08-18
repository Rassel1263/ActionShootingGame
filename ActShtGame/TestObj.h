#pragma once

class TestObj : public Object
{
public:
	Sprite spr;
	RenderInfo info;

	TestObj();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

