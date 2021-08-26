#pragma once
class HelpPage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	HelpPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

