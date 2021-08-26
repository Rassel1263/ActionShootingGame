#pragma once
class EnemyManager : public Object
{
public:
	float spawnTimer = 0.0f;
	float spawnTime = 0.0f;
	EnemyName name = EnemyName::BULLET_KIM;

	EnemyManager(D3DXVECTOR2 pos, EnemyName name, float spawnTime); 

	virtual void Update(float deltaTime);
	virtual void Render();
	void SpawnEnemy();
};

