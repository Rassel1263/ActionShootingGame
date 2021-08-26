#include "Header.h"

GameOver::GameOver()
{
	bg.LoadAll(L"Assets/Sprites/UI/fade.png");
	font.LoadAll(L"Assets/Sprites/UI/GameOver.png");
	bg.bCamera = false;
	font.bCamera = false;
	bg.color.a = 0.0f;

	layer = 1200;
}

void GameOver::Update(float deltaTime)
{
	if (bg.color.a < 1.0f)
	{
		bg.color.a += Game::GetInstance().unscaleTime;
		font.color.a = bg.color.a;
	}
	else
	{
		if (Input::GetInstance().KeyDown(VK_SPACE))
		{
			Game::GetInstance().timeScale = 1.0f;
			Game::GetInstance().ChangeScecne(new MainScene());
		}
	}
}

void GameOver::Render()
{
	bg.Render({});
	font.Render({});
}
