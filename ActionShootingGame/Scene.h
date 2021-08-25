#pragma once

class Scene
{
public:
	static float score;
	float destScore = 0.0f;

	ObjectManager obm;
	MapManager* mapManager = NULL;
	Scene* nextScene = NULL;
	Mouse* mouse = NULL;
	Player* player = NULL;
	std::vector<CEnemy*> enemyVecs;
	std::random_device rd;

	std::wstring curStage = L"";

	bool bossZoom = false;
	bool gameScene = true;
	bool spawnBoss = false;
	bool stageClear = false;

	float gameTime = 180.0f;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void AddScore(float score);
	void SortEnemyVector(CEnemy* enemy);
};

