#include "Header.h"

EnemyManager::EnemyManager(D3DXVECTOR2 pos, EnemyName name)
{
	this->pos = pos;
	this->name = name;
}

void EnemyManager::Update(float deltaTime)
{
	if (name == EnemyName::SHOTGAT) return;

	spawnTimer += deltaTime;

	if (spawnTimer > 5.0f)
	{
		if (name == EnemyName::SHOTGAT)
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

	if (name == EnemyName::BULLET_KIM)
		nowScene->obm.AddObject(enemy = new BulletKim(pos));

	if (name == EnemyName::SHOTGUN_KIN)
		nowScene->obm.AddObject(enemy = new ShotgunKin(pos));

	if(name == EnemyName::BANBULLET_KIN)
		nowScene->obm.AddObject(enemy = new BanBulletKin(pos));

	if (name == EnemyName::SHOTGAT)
		nowScene->obm.AddObject(enemy = new Shotgat(pos));

	nowScene->enemyVecs.push_back(enemy);

	if (nowScene->spawnBoss)
		destroy = true;
}
