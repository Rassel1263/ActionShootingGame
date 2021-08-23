#pragma once
class Fade : public Object
{
public:
	Sprite fade;

	bool fill = false;

	Fade(bool fill);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

