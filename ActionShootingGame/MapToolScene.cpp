#include "Header.h"
#include "MapToolScene.h"

void MapToolScene::Init()
{
	obm.AddObject(new MapToolMouse());

	obm.AddObject(mapManager = new MapManager(L"GameScene1/map00", L"GameScene1/map01"));

	obm.AddObject(new MapToolBlock(L"00", D3DXVECTOR2(-218, 0)));
	obm.AddObject(new MapToolBlock(L"01", D3DXVECTOR2(-200, 0)));
	obm.AddObject(new MapToolBlock(L"02", D3DXVECTOR2(-182, 0)));

	obm.AddObject(new MapToolBlock(L"03", D3DXVECTOR2(-218, -18)));
	obm.AddObject(new MapToolBlock(L"04", D3DXVECTOR2(-200, -18)));
	obm.AddObject(new MapToolBlock(L"05", D3DXVECTOR2(-182, -18)));

	obm.AddObject(new MapToolBlock(L"06", D3DXVECTOR2(-218, -36)));
	obm.AddObject(new MapToolBlock(L"07", D3DXVECTOR2(-200, -36)));
	obm.AddObject(new MapToolBlock(L"08", D3DXVECTOR2(-182, -36)));
}

void MapToolScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MapToolScene::Render()
{
	Scene::Render();
}
