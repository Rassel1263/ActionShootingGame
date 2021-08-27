#include "Header.h"

EnemyManager::EnemyManager(D3DXVECTOR2 pos, Unit::UnitName name, float spawnTime)
{
	this->pos = pos;
	this->name = name;
	std::default_random_engine rnd(nowScene->rd());
	std::uniform_int_distribution<int> dis(0, nowScene->stage - 1);

	this->spawnTime = spawnTime - dis(rnd) * 0.1f;
}

void EnemyManager::Update(float deltaTime)
{
	spawnTimer += deltaTime;

	if (spawnTimer > spawnTime)
	{
		if (name == Unit::UnitName::SHOTGAT)
		{
			std::random_device rd;
			std::default_random_engine rnd(rd());
			std::uniform_int_distribution<int> dis(1, 100);

			pos = D3DXVECTOR2(pos.x + dis(rnd), pos.y + dis(rnd));
		}

		nowScene->obm.AddObject(new CEffect(L"Spawn/before", pos, 0.05f, D3DXVECTOR2(1, 1), [&] {SpawnEnemy(); }));
		spawnTimer = 0.0f;
	}
}

void EnemyManager::Render()
{
}

void EnemyManager::SpawnEnemy()
{
	CEnemy* enemy = NULL;

	if (name == Unit::UnitName::BULLET_KIM)
		nowScene->obm.AddObject(enemy = new BulletKim(pos));

	if (name == Unit::UnitName::SHOTGUN_KIN)
		nowScene->obm.AddObject(enemy = new ShotgunKin(pos));

	if(name == Unit::UnitName::BANBULLET_KIN)
		nowScene->obm.AddObject(enemy = new BanBulletKin(pos));

	if (name == Unit::UnitName::SHOTGAT)
		nowScene->obm.AddObject(enemy = new Shotgat(pos));

	nowScene->enemyVecs.push_back(enemy);

	if (nowScene->spawnBoss)
		destroy = true;
}
