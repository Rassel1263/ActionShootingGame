#include "Header.h"

void GameScene::Init()
{
	srand(time(NULL));

	obm.AddObject(new Fade(false));
	obm.AddObject(mapManager = new MapManager(L"GameScene1/room1/map00", L"GameScene1/room1/map01"));
	//obm.AddObject(new BulletKim(D3DXVECTOR2(400, 200)));
	//obm.AddObject(player = new Player(D3DXVECTO));
	obm.AddObject(mouse = new Mouse());
}

void GameScene::Update(float deltaTime)
{
	gameTime -= deltaTime;

	if (gameTime < 175.0f && !tutorial)
	{
		tutorial = true;
		obm.AddObject(new TutorialScroll());
	}

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
