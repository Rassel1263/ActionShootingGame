#include "Header.h"

void GameScene::Init()
{
	nextScene = new GameScene2();

	ShaderManager::GetInstance().CreateEffect("Glow", L"Assets/Shader/glowShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/whiteShader.fx", 1);

	curStage = L"GameScene1/";
	srand(time(NULL));

	obm.AddObject(new Fade(false));
	obm.AddObject(mapManager = new MapManager(curStage + L"room1/map00", curStage + L"room1/map01"));
	obm.AddObject(new Elevator(player->spawnPos, true));
	obm.AddObject(new Minimap());
	obm.AddObject(new Font(L"Number", D3DXVECTOR2(-10, 110), gameTime, D3DXVECTOR2(1.6, 1.6), 15));
	obm.AddObject(new Font(L"Number", D3DXVECTOR2(200, 110), score, D3DXVECTOR2(1.0, 1.0), 10));
	//obm.AddObject(new GatlingGull(D3DXVECTOR2(400, 200)));
	
	//obm.AddObject(player = new Player(D3DXVECTO));
	obm.AddObject(mouse = new Mouse());
}

void GameScene::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('G'))
	{
		CEnemy* enemy;
		obm.AddObject(enemy = new BulletKim(player->spawnPos));
		enemyVecs.push_back(enemy);
	}

	if (tutorial)
	{
		tutorialTimer += deltaTime;

		if (tutorialTimer >= 5.0f)
		{
			tutorialTimer = -999.0f;
			obm.AddObject(new TutorialScroll());
		}
	}
	else
	{
		if(!stageClear) gameTime -= deltaTime;

		if (gameTime <= 170 && !spawnBoss)
		{
			spawnBoss = true;
			obm.AddObject(new CEffect(L"Spawn/before", player->spawnPos, 0.05f, D3DXVECTOR2(2, 2), [&]() { SpawnBoss(); }));
		}
	}

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::SpawnBoss()
{
	obm.AddObject(new GatlingGull(player->spawnPos + D3DXVECTOR2(0, -50)));
}

