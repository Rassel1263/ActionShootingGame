#include "Header.h"

EnemyManager::EnemyManager(D3DXVECTOR2 pos, EnemyName name)
{
	this->pos = pos;
	this->name = name;
}

void EnemyManager::Update(float deltaTime)
{
	spawnTimer += deltaTime;

	if (spawnTimer > 5.0f)
	{
		nowScene->obm.AddObject(new CEffect(L"Spawn/before", pos, 0.05f, D3DXVECTOR2(1, 1), [&] {SpawnEnemy(); }));
		spawnTimer = 0.0f;
	}
}

void EnemyManager::Render()
{
}

void EnemyManager::SpawnEnemy()
{
	if (name == EnemyName::BULLET_KIM)
		nowScene->obm.AddObject(new BulletKim(pos));

	if (name == EnemyName::SHOTGUN_KIN)
		nowScene->obm.AddObject(new ShotgunKin(pos));
}
