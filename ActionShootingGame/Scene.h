#pragma once

class Scene
{
public:
	ObjectManager obm;
	MapManager* mapManager = NULL;
	Mouse* mouse = NULL;
	Player* player = NULL;

	bool gameScene = true;
	float gameTime = 180.0f;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

