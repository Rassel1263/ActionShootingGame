#include "Header.h"

TestPixel::TestPixel()
{
	spr.LoadAll(L"Assets/Sprites/pixel.png");

	Collider::AABB aabb;
	aabb.min = { -1, -1 };
	aabb.max = { 1, 1 };
	bodies.push_back(Collider(this, L"", &aabb));
}

void TestPixel::Update(float deltaTime)
{

}

void TestPixel::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}
