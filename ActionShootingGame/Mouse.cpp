#include "Header.h"

Mouse::Mouse()
{
	bCamera = false;
	mouseSpr.bCamera = false;
	mouseSpr.LoadAll(L"Assets/Sprites/UI/MousePointer.png");

	Collider::AABB aabb;
	aabb.min = { -1, -1 };
	aabb.max = { 1, 1 };
	bodies.push_back(Collider(this, L"mouse", &aabb));

	layer = 10;
}

void Mouse::Update(float deltaTime)
{
	pos = Input::GetInstance().GetFixedMousePos();
}

void Mouse::Render()
{
	mouseRI.pos = pos;
	mouseSpr.Render(mouseRI);

	Object::Render();
}
