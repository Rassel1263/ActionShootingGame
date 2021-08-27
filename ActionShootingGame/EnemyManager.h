#pragma once
class EnemyManager : public Object
{
public:
	float spawnTimer = 0.0f;
	float spawnTime = 0.0f;
	Unit::UnitName name = Unit::UnitName::BULLET_KIM;

	EnemyManager(D3DXVECTOR2 pos, Unit::UnitName name, float spawnTime); 

	virtual void Update(float deltaTime);
	virtual void Render();
	void SpawnEnemy();
};

