#include "Header.h"

void GameScene::Init()
{
	srand(time(NULL));

	obm.AddObject(mapManager = new MapManager(L"GameScene1/room2/map00", L"GameScene1/room2/map01"));
	obm.AddObject(new BulletKim(D3DXVECTOR2(40, 0)));
	obm.AddObject(new BulletKim(D3DXVECTOR2(400, 0)));
	obm.AddObject(new ShotgunKin(D3DXVECTOR2(400, 200)));
	//obm.AddObject(player = new Player(D3DXVECTO));
	obm.AddObject(mouse = new Mouse());
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
