#pragma once
class EnemyManager : public Object
{
public:
	float spawnTimer = 0.0f;

	EnemyManager();

	virtual void Update(float deltaTime);
	virtual void Render();
};

