#include "Header.h"

void GameScene::Init()
{
	srand(time(NULL));

	obm.AddObject(new Fade(false));
	obm.AddObject(mapManager = new MapManager(L"GameScene1/room1/map00", L"GameScene1/room1/map01"));
	obm.AddObject(new Font(L"Number", D3DXVECTOR2(-10, 110), gameTime, D3DXVECTOR2(1.6, 1.6), 15));
	obm.AddObject(new BulletKim(D3DXVECTOR2(400, 200)));
	//obm.AddObject(player = new Player(D3DXVECTO));
	obm.AddObject(mouse = new Mouse());
}

void GameScene::Update(float deltaTime)
{
	if (tutorial)
	{
		tutorialTimer += deltaTime;

		if (tutorialTimer >= 5.0f)
		{
			tutorialTimer = -999.0f;
			obm.AddObject(new TutorialScroll());
		}
	}
	else
	{
		gameTime -= deltaTime;
	}

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
