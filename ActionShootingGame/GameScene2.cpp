#include "Header.h"

void GameScene2::Init()
{
	nextScene = new GameScene3();

	curStage = L"GameScene2/";
	srand(time(NULL));

	obm.AddObject(new Fade(false));
	obm.AddObject(mapManager = new MapManager(curStage + L"room1/map00", curStage + L"room1/map01"));
	obm.AddObject(new Elevator(player->spawnPos, true));
	obm.AddObject(new Font(L"Number", D3DXVECTOR2(-10, 110), gameTime, D3DXVECTOR2(1.6, 1.6), 15));
	obm.AddObject(new Font(L"Number", D3DXVECTOR2(200, 110), score, D3DXVECTOR2(1.0, 1.0), 10));
	//obm.AddObject(new GatlingGull(D3DXVECTOR2(400, 200)));
	//obm.AddObject(player = new Player(D3DXVECTO));
	obm.AddObject(mouse = new Mouse());
}

void GameScene2::Update(float deltaTime)
{
	if (!stageClear) gameTime -= deltaTime;

	if (gameTime <= 170 && !spawnBoss)
	{
		spawnBoss = true;
		obm.AddObject(new CEffect(L"Spawn/before", player->spawnPos, 0.05f, D3DXVECTOR2(2, 2), [&]() { SpawnBoss(); }));
	}

	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}

void GameScene2::SpawnBoss()
{
	obm.AddObject(new GatlingGull(player->spawnPos + D3DXVECTOR2(0, -50)));
}
