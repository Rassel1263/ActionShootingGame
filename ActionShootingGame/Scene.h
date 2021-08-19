#pragma once

class Scene
{
public:
	ObjectManager obm;
	MapManager* mapManager = NULL;
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

