#include "Header.h"

Fade::Fade(bool fill)
{
	fade.bCamera = false;
	this->fill = fill;
	fade.LoadAll(L"Assets/Sprites/UI/fade.png");

	(fill) ? fade.color.a = 0.0 : fade.color.a = 1.0f;

	layer = 99;
}

void Fade::Update(float deltaTime)
{
	if (fill)
	{
		fade.color.a += deltaTime;

		if (fade.color.a >= 1.0f)
			destroy = true;
	}
	else
	{
		fade.color.a -= deltaTime;

		if (fade.color.a <= 0.0f)
			destroy = true;
	}
}

void Fade::Render()
{
	fade.Render({pos});
}
