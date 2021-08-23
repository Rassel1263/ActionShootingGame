#pragma once
class TutorialScroll : public Object
{
public:
	float timer = 0.0f;

	Sprite scroll;
	Sprite paint;

	TutorialScroll();

	virtual void Update(float deltaTime);
	virtual void Render();
};

