#include "Header.h"

void GameScene::Init()
{
	obm.AddObject(mapManager = new MapManager(L"GameScene1/map00", L"GameScene1/map01"));
	obm.AddObject(new Player());

}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
