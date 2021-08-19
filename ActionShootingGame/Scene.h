#pragma once

class Scene
{
public:
	ObjectManager obm;
	MapManager* mapManager = NULL;
	Mouse* mouse = NULL;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

