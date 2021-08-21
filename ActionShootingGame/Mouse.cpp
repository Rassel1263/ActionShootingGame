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

D3DXVECTOR2 Mouse::GetMouseDir()
{
	D3DXVECTOR2 mouseDir = { 0, 0 };
	D3DXVec2Normalize(&mouseDir, &pos);
	return mouseDir;
}

float Mouse::GetMouseAngleToRadian(bool reverseY, D3DXVECTOR2 centerPos)
{
	D3DXVECTOR2 mousePos = pos - centerPos;
	D3DXVec2Normalize(&mousePos, &mousePos);
	float radian = atan2((reverseY) ? -mousePos.y : mousePos.y, mousePos.x);

	return radian;
}

float Mouse::GetMouseAngleToDegree(bool reverseY, D3DXVECTOR2 centerPos)
{
	return D3DXToDegree(GetMouseAngleToRadian(reverseY, centerPos));
}

