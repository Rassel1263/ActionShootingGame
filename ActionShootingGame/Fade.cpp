#include "Header.h"

Fade::Fade(bool fill, float timer, std::function<void()> func)
{
	fade.bCamera = false;
	this->fill = fill;
	this->timer = timer;
	this->maxTimer = timer;
	fade.LoadAll(L"Assets/Sprites/UI/fade.png");

	(fill) ? fade.color.a = 0.0 : fade.color.a = 1.0f;
	this->func = func;

	layer = 1050;
}

void Fade::Update(float deltaTime)
{
	if (fill)
	{
		timer -= deltaTime;

		fade.color.a = (maxTimer - timer) / maxTimer;

		if (fade.color.a >= 1.3f)
		{
			if (func) func();
			destroy = true;
		}
	}
	else
	{
		timer -= deltaTime;

		fade.color.a = timer / maxTimer;

		if (fade.color.a <= 0.0f)
		{
			if (func) func();
			destroy = true;
		}
	}
}

void Fade::Render()
{
	fade.Render({ pos });
}
