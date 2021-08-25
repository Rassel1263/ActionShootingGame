#include "Header.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	if (destScore > 0.0f)
	{
		float tempNum = destScore;
		destScore -= deltaTime * 500;

		score += tempNum - destScore;
	}

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScecne(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScecne(new GameScene2());

	if (Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScecne(new GameScene3());

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::AddScore(float score)
{
	destScore = score;
}

void Scene::SortEnemyVector(CEnemy* enemy)
{
	enemyVecs.erase(std::find(enemyVecs.begin(), enemyVecs.end(), enemy));
}
