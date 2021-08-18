#include "DXUT.h"
#include "Scene.h"

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	obm.OnCollision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

