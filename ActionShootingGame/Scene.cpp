#include "Header.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	if (stage > 0 && stage < 4)
	{
		if (destScore > 0.0f)
		{
			float tempNum = destScore;
			destScore -= deltaTime * 500;

			score += tempNum - destScore;
		}

		if (Input::GetInstance().KeyDown(VK_F1))
		{
			nowScene->player->god = !nowScene->player->god;
		}

		if (Input::GetInstance().KeyDown(VK_F2))
		{
			nowScene->player->LevelUp();
		}

		if (Input::GetInstance().KeyDown(VK_F3))
		{
			for (auto enemy : enemyVecs)
			{
				if (enemy->pos.x > Camera::GetInstance().cameraPos.x - 240 &&
					enemy->pos.x < Camera::GetInstance().cameraPos.x + 240 &&
					enemy->pos.y > Camera::GetInstance().cameraPos.y - 135 &&
					enemy->pos.y < Camera::GetInstance().cameraPos.y + 135)
				{
					enemy->Die();
				}
			}
		}
	}

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScecne(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScecne(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScecne(new GameScene2());

	if (Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScecne(new GameScene3());


	if (Input::GetInstance().KeyDown(VK_F8))
		Game::GetInstance().ChangeScecne(new RankingScene());



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
