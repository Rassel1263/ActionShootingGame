#include "Header.h"

void RankingScene::Init()
{
	obm.AddObject(new Ranking());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	Scene::Render();
}
