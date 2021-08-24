#pragma once
class Fade : public Object
{
public:
	Sprite fade;

	bool fill = false;
	float timer = 0.0f;
	float maxTimer = 0.0f;
	std::function<void()> func;

	Fade(bool fill, float timer = 1.0f, std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

