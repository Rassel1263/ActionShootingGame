#include "Header.h"

void GameScene::Init()
{
	obm.AddObject(mapManager = new MapManager(L"GameScene1/map00", L"GameScene1/map01"));
	obm.AddObject(new BulletKim(D3DXVECTOR2(40, 0)));
	obm.AddObject(new BulletKim(D3DXVECTOR2(400, 0)));
	obm.AddObject(player = new Player());
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
