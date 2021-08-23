#include "Header.h"

Elevator::Elevator(D3DXVECTOR2 pos)
{
	this->pos = pos + D3DXVECTOR2(0, 30);

	floor.LoadAll(L"Assets/Sprites/Elevator/floor");
	husks.LoadAll(L"Assets/Sprites/Elevator/husks", 0.1f, false);

	layer = 2;
}

void Elevator::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f)
	{
		floor.color.a -= deltaTime;
		husks.color.a -= deltaTime;

		if (floor.color.a <= 0.0f)
			destroy = true;
	}

	husks.Update(deltaTime);
}

void Elevator::Render()
{
	//floor.Render({ pos });
	husks.Render({ pos });
}
