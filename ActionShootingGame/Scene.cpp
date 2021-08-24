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
