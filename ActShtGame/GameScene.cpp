#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	obm.AddObject(new TestObj());
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
