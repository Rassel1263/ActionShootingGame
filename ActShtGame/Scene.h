#pragma once
class Scene
{
public:
	ObjectManager obm;
	Scene* nextScene = NULL;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

