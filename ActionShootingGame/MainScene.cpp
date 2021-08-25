#include "Header.h"

void MainScene::Init()
{
	nextScene = new GameScene();

	curStage = L"MainsCene";

	obm.AddObject(new Main());
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
