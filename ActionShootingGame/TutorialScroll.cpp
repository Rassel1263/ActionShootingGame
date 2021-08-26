#include "Header.h"

TutorialScroll::TutorialScroll()
{
	scroll.LoadAll(L"Assets/Sprites/UI/Scroll.png");
	scroll.color.a = 0.0f;
	scroll.bCamera = false;

	paint.LoadAll(L"Assets/Sprites/UI/Paint");
	paint.bCamera = false;
	paint.color.a = 0.0f;

	layer = 5;

	layer = 1060;
}

void TutorialScroll::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('X'))
	{
		Camera::GetInstance().cameraQuaken = { 100, 100 };
		nowScene->mapManager->ChangeMap(L"GameScene1/room2/map00", L"GameScene1/room2/map01");
		static_cast<GameScene*>(nowScene)->tutorial = false;
		destroy = true;
	}

	if (scroll.color.a >= 1.0f)
	{
		if (paint.color.a < 1.0f)
			paint.color.a += deltaTime;

		timer += deltaTime;
		if (timer >= 5.0f)
		{
			paint.scene = 1;
		}

		if (timer >= 10.0f)
		{
			pos.y -= deltaTime * 800;

		}

		if (timer >= 10.5f)
		{
			Camera::GetInstance().cameraQuaken = { 100, 100 };
			nowScene->mapManager->ChangeMap(L"GameScene1/room2/map00", L"GameScene1/room2/map01");
			static_cast<GameScene*>(nowScene)->tutorial = false;
			destroy = true;
		}
	}
	else
		scroll.color.a += deltaTime;
}

void TutorialScroll::Render()
{
	scroll.Render({ pos });
	paint.Render({ pos });
}
