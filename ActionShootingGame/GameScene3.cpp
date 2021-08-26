#include "Header.h"

void GameScene3::Init()
{
	srand(time(NULL));

	nextScene = new RankingScene();

	curStage = L"GameScene3/";
	stage = 3;
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

void GameScene3::Update(float deltaTime)
{
	if (!stageClear && !nowScene->player->intro) gameTime -= deltaTime;

	if (gameTime <= 60 && !spawnBoss)
	{
		spawnBoss = true;
		obm.AddObject(new CEffect(L"Spawn/before", player->spawnPos, 0.05f, D3DXVECTOR2(2, 2), [&]() { SpawnBoss(); }));
	}

	Scene::Update(deltaTime);
}

void GameScene3::Render()
{
	Scene::Render();
}

void GameScene3::SpawnBoss()
{
	obm.AddObject(new HighPriest(player->spawnPos + D3DXVECTOR2(0, -50)));
}
