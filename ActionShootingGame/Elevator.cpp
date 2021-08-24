#include "Header.h"

Elevator::Elevator(D3DXVECTOR2 pos, bool stageStart)
{
	this->pos = pos + D3DXVECTOR2(0, 30);

	floor.LoadAll(L"Assets/Sprites/Elevator/floor");
	husks[0].LoadAll(L"Assets/Sprites/Elevator/husks/Up", 0.1f, false);
	husks[1].LoadAll(L"Assets/Sprites/Elevator/husks/Down", 0.1f, false);

	Collider::AABB aabb;
	aabb.min = { -10, -30 };
	aabb.max = { 10, -10 };
	bodies.push_back(Collider(this, L"elevator", &aabb));

	this->stageStart = stageStart;

	layer = 2;
}

void Elevator::Update(float deltaTime)
{
	timer -= deltaTime;

	if (stageStart)
	{
		if (!husks[0].bAnimation)
			nowScene->player->intro = false;

		if (timer <= 0.0f)
		{
			floor.color.a -= deltaTime;
			husks[0].color.a -= deltaTime;

			if (floor.color.a <= 0.0f)
				destroy = true;
		}
	}
	else
	{
		if (boarding)
		{
			if (!drawFade)
			{
				nowScene->player->intro = true;
				renderNum = 1;
				auto func = [] { Game::GetInstance().ChangeScecne(nowScene->nextScene); };
				nowScene->obm.AddObject(new Fade(true, 1.0f, func));

				drawFade = true;
			}
		}
	}

	husks[renderNum].Update(deltaTime);
}

void Elevator::Render()
{
	//floor.Render({ pos });
	husks[renderNum].Render({ pos });

	Object::Render();
}

void Elevator::OnCollision(Collider& coli)
{
	if (coli.tag == L"ally")
	{
		boarding = true;
	}
}
