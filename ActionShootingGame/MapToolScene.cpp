#include "Header.h"
#include "MapToolScene.h"

void MapToolScene::Init()
{
	gameScene = false;
	obm.AddObject(new MapToolMouse());

	obm.AddObject(mapManager = new MapManager(L"GameScene1/map00", L"GameScene1/map01"));

	obm.AddObject(new MapToolBlock(L"00", D3DXVECTOR2(-218, 0)));
	obm.AddObject(new MapToolBlock(L"01", D3DXVECTOR2(-200, 0)));
	obm.AddObject(new MapToolBlock(L"02", D3DXVECTOR2(-182, 0)));

	obm.AddObject(new MapToolBlock(L"03", D3DXVECTOR2(-218, -18)));
	obm.AddObject(new MapToolBlock(L"04", D3DXVECTOR2(-200, -18)));
	obm.AddObject(new MapToolBlock(L"05", D3DXVECTOR2(-182, -18)));
	obm.AddObject(new MapToolBlock(L"06", D3DXVECTOR2(-164, -18)));
	obm.AddObject(new MapToolBlock(L"07", D3DXVECTOR2(-146, -18)));

	obm.AddObject(new MapToolBlock(L"08", D3DXVECTOR2(-218, -36)));
	obm.AddObject(new MapToolBlock(L"09", D3DXVECTOR2(-200, -36)));
	obm.AddObject(new MapToolBlock(L"10", D3DXVECTOR2(-182, -36)));

	obm.AddObject(new MapToolBlock(L"11", D3DXVECTOR2(-218, -54)));
	obm.AddObject(new MapToolBlock(L"12", D3DXVECTOR2(-200, -54)));
	obm.AddObject(new MapToolBlock(L"13", D3DXVECTOR2(-182, -54)));

	obm.AddObject(new MapToolBlock(L"14", D3DXVECTOR2(-218, -72)));
	obm.AddObject(new MapToolBlock(L"15", D3DXVECTOR2(-200, -72)));

}

void MapToolScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MapToolScene::Render()
{
	Scene::Render();
}
